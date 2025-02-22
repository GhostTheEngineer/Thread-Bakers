# Change Log
This document reflects this current commit's state and not just its version. All items listed below were implemented for this commit.

## Version v1.0.1
This update fixes a thread synchronization issues with static function variables, `rd` and `gen` of `getRandomWorkTime`.

### Addition
- None

### Changes
- None

### Fixes
- The static variables in the function, `getRandomWorkTime`, were not protected in the files that used thread synchronization. Now the `workTime` variable in the function `baker` initializes to 0 and the call to `getRandomWorkTime` happens within locked mutex.