# World-map Mario spawn (USA v1.3.0)

## Pose vs checkpoint vs player fields

MainGame map return pose (seeded on course-out / directed open):

- `+0x19C` world
- `+0x1A0` section (0 or 1; path index `(world << 1) + section`)
- `+0x1A4` node index into `CourseSelectNodePath`
- `+0x1A8` course tag (pack course number)
- `+0x2C` bit 3 (`|= 8`): pose-valid gate read by `CourseSelectPlayer::create_`

FieldGameData checkpoint (`setCheckPoint` `0x024BADF4`) is separate.

- Written on normal map enter from save (`0x0250C76C` inside `f_0250C3EC`).
- Directed `nsmbu open` / `run` skips that path, so `CheckPointData::index` stays `-1`.
- `enterMapFromGameData_` (`0x024C2230`) clears the checkpoint when `checkEnterCourse` fails.

CourseSelectPlayer / CourseSelectDemoActor:

- `+0xF0` world
- `+0xF4` section
- `+0xF8` extra param (often 0; may be `-1` during setup)
- `+0xFC` course/slot id — must match `getCourseSlotFromPose` → node `+0x58`

Ctor copies these from `ActorCreateParam` bytes `+0x20..+0x24`.
Game code often overwrites `F0/F4/F8` to `-1` before spawn finishes.

## Path node identity

Nodes are `0x68` bytes (`CourseSelectPathNode`).

- Name at `*(node+0)` — e.g. `W101` = pack 1-1.
  Prefer this for course identity.
- Floats at `+0x44 / +0x48 / +0x4C` = position.
- `+0x50 / +0x54` are **not** reliable world/course (often `0,0` on both W1S0 and W101).
- `+0x58` = course/slot id (`getCourseSlotFromPose` / `0x02242C70`).
- `+0x5C` looks like node index.

Map paths live at `CourseSelectMgr+0x60` (`getMapPath` `0x021F9FEC`).
`getPath` `0x021F9FC8` is a second table at `+0x18`.

## create_ gate (`0x0226FBC4`, site `0x0226FD14`)

After path resolve:

1. `getCourseSlotFromPose` → node `+0x58`
2. `getCourseSelectNodeType` (`0x021EF6C8`)
3. Require MainGame `+0x2C` bit 3
4. Require type `== 2` (ids 20/21 via `f_024D37EC`)
5. Require player `+0xF0 ==` pose world and `+0xFC ==` course_slot

Type `0` is regular courses `0..11` (`f_024D37A0`).
Those fail step 4 and take `L_02270268` (query helpers, often `ActorMgr::createLater` at `0x02270368`).

## Course-out

1. `AreaTask::requestCourseOut_Normal` (`0x024B77DC`):
   MainGame `+0x20 = 2`, `+0x24 = 0`, AreaTask `+0x730 = 3`
   The opening `BossDemo` (`0x0202F0E0`) uses this same call, so exit type `2` is also the cinematic handoff.
   Applying an existing save (`f_029D7648`) calls `f_029CF2D0`, which stores exit type `1` at `MainGame+0x20`.
   Exit type alone cannot tell a file load or the cinematic from quitting a course.
   Map-return seeding has to wait for `prepareCourseOut` (`0x024B8324`).
2. Later `prepareCourseOutEnter` (`0x024B82A4`):
   `CourseInfo::setNextSceneEnterType(3)`, then `setCourseOut` (`0x024B814C` → `+0x74D = 1`)
3. Site `0x024B8324` is immediately before `setCourseOut` (runtime seeds pose here)

## Observed mismatch

Player actor sat at W1S0 xyz `(-2950, 117.5, 3370)` while MainGame pose was W101 `(-5200, 57.5, 3490)`.

`CheckPointData.index` is the path node index.
`W101` is node 1.
`node+0x58` for that node is course slot 0.
That value is also W1S0's node index.
Writing the course slot as the checkpoint index makes the map camera and title use W1S0 (Blooper's Secret Lair).

`CourseSelectPlayer+0x110` is `mModelPos` only while `create_` packs `createLater`.
After spawn it is a live object pointer.
Writing floats there faults in `NMSndObject::calc` (`ld` at `+0xC`).

`CourseSelectMap::calc` (`0x021F6FE8`) runs only when `CourseSelectTask+0xDC9` is 0.
The map camera goal tracks the checkpoint node, not `CourseSelectPlayer+0x50`.
Focus setup at `0x0227CCF4` and `0x0227E2A8` copies the path-search node (`+0x50/+0x54/+0x5C` and position `+0x44`) into the camera.
After a directed open that search still returns the world start, so those sites replace `r3` with the named course node before the stores.
