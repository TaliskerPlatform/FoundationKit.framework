# Talisker
## Foundation Toolkit

**This is currently pre-alpha quality code. All interfaces ought to be considered unstable.**

### Building with Docker

Once you have cloned this repository, you can run the following:

```
$ Resources/Docker/build
FoundationKit Docker build tool

Usage (from top of FoundationKit source tree):
  Resources/Docker/build all       Build for all targets
  Resources/Docker/build clean     Remove build files
  Resources/Docker/build prepare   Ensure base images exist
  Resources/Docker/build update    Update base images
  Resources/Docker/build list      List available targets
  Resources/Docker/build TARGET    Build for TARGET

Available targets:
  jessie
  precise
  stretch
  trusty
  wheezy
  xenial
```

You can build for a single target by specifying its name:

```
$ Resources/Docker/build jessie
```

Or you can build for each of the targets in turn:

```
$ Resources/Docker/build all
```

The `prepare` operand creates base images for each of the targets (whose `Dockerfile`s can be found in
[`Resources/Docker/*`](Resources/Docker)), and is invoked automatically as part of a build, but you can run it manually
if you wish. If you want to update your base images, you can use:

```
$ Resources/Docker/build update
```

While building, `Resources/Docker/build` will create and use a `DockerBuild` directory. You can remove this with:

```
$ Resources/Docker/build clean
```

Alternatively, you can remove it yourself at any time a Docker build is not in progress.

### Copyright & Licence

Copyright © 2012-2017 Mo McRoberts.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

### Third-party Software

This project incorporates (via Git submodules), the following:

* [uriparser](https://github.com/uriparser/uriparser) by Weijia Song and Sebastian Pipping, licensed according to the terms of a [BSD-like license](https://github.com/uriparser/uriparser/blob/9037441b2acc8e4f779d5ad0388c218901c77f74/COPYING).
* [uthash](https://github.com/troydhanson/uthash) by Troy D. Hanson, licensed according to the terms of a [MIT/X11-style licence](https://github.com/troydhanson/uthash/blob/3fbec3efe5b5645852c3c123fae9b3a419c929f9/LICENSE).

See the [`ThirdParty`](ThirdParty) directory for further details.
