# Talisker
## Foundation Toolkit

[![Current build status][travis]](https://travis-ci.org/TaliskerPlatform/FoundationKit.framework)
[![Apache 2.0 licensed][licence]](#copyright--licence)
![Implemented in C++][language]

**This is currently pre-alpha quality code. All interfaces ought to be considered unstable.**

* [Introduction](#introduction)
* [Get the Foundation Toolkit](#get-the-foundation-toolkit)
  * [Installing binary packages](#installing-binary-packages)
  * [Building from a distribution tarball](#building-from-a-distribution-tarball)
  * [Cloning this repository](#cloning-this-repository)
* [Building from source](#building-from-source)
  * [Preparing the source tree](#preparing-the-source-tree)
  * [Configuration](#configuration)
  * [Building](#building)
  * [Installation](#installation)
* [Building with Docker](#building-with-docker)
* [Copyright & licence](#copyright--licence)
  * [Third-party software](#third-party-software)

### Introduction

The _Talisker Foundation Toolkit_, or "FoundationKit" for short, is a portable collection of basic COM interfaces and foundational classes.

### Get the Foundation Toolkit

#### Installing binary packages

There are currently no binary packages of the Foundation Toolkit available. This is expected to change as the project matures.

To use Foundation Toolkit, you must  instead [clone the repository](#cloning-the-repository) and [build from source](#building-from-source).

#### Building from a distribution tarball

There are currently no distribution tarballs of the Foundation Toolkit available. This is expected to change as the project matures.

To use Foundation Toolkit, you must instead [clone the repository](#cloning-the-repository) and [build from source](#building-from-source).

#### Cloning this repository

If there are no suitable binary packages or distribution tarballs available, or if you just wish to try out the latest bleeding-edge development version of the Foundation Toolkit, you can clone the [source repository](https://github.com/TaliskerPlatform/FoundationKit.framework) and build that instead.

First, clone the repository itself:

```
$ git clone --branch=develop https://github.com/TaliskerPlatform/FoundationKit.framework.git FoundationKit
Cloning into 'FoundationKit'...
remote: Counting objects: 225, done.
remote: Compressing objects: 100% (126/126), done.
remote: Total 225 (delta 117), reused 181 (delta 75), pack-reused 0
Receiving objects: 100% (225/225), 56.80 KiB | 653.00 KiB/s, done.
Resolving deltas: 100% (117/117), done.
```

Now, change into the `FoundationKit` directory and fetch the _sub-modules_:

```
$ cd FoundationKit
$ git submodule update --init --recursive
Submodule 'ThirdParty/uriparser' (git://github.com/uriparser/uriparser.git) registered for path 'ThirdParty/uriparser'
Submodule 'ThirdParty/uthash' (git://github.com/troydhanson/uthash.git) registered for path 'ThirdParty/uthash'
...
$
```

Now that you've cloned the repository and its sub-modules, you can either proceed to [building the tree from source directly](#building-from-source). Alternatively, if you have [Docker](https://docker.com) for Mac or Linux installed, you can [perform builds with Docker](#building-with-docker).

### Building from source

**Note**: You can use [Docker](https://docker.com) to orchestrate your build process if you prefer; see the _[Building with Docker](#building-with-docker)_ section, below, for further information.

#### Preparing the source tree

If you have [cloned this repository](#cloning-this-repository), you will need to prepare it for building from source using `autoreconf`. You will need to re-run `autoreconf` when you fetch upstream changes which modify the build logic (`configure.ac`, any `Makefile.am` files, etc.).

You should skip this step if you obtained the sources from a distribution tarball.

Change to the directory that you cloned `FoundationKit` into:

```
$ autoreconf -fvi
autoreconf: Entering directory `.'
autoreconf: configure.ac: not using Gettext
...
$
```

The options passed to `autoreconf` here are:

* `-v`: be verbose; you can omit this if you wish
* `-i`: install; copy missing build scripts into the source tree from the versions supplied with `autoconf`/`automake`, etc.
* `-f`: force; updates build scripts with the versions installed on your local system


#### Configuration

Next, you can use `configure` and `make` as you would any other Autotools-based project:

```
$ ./configure [STANDARD CONFIGURE OPTIONS]
...
```

e.g.:

```
$ ./configure --prefix=/opt/talisker
```

#### Building

Once configured successfully, you can build the Foundation Toolkit:
```
$ make
...
```

The `make check` target is used to run automated tests:

```
$ make check
...
```

#### Installation

As is conventional, you can use `make install` to install the Foundation Toolkit onto your system:

```
$ sudo make install
Password:
...
```

On Darwin-based systems (macOS, iOS, tvOS and watchOS), Foundation Toolkit will be installed as `/Library/Frameworks/FoundationKit.framework` and can be used via `-framework FoundationKit`.

On other systems, Foundation Toolkit is installed to `${libdir}` and `${includedir}` and can be used via `-lFoundationKit`.

### Building with Docker

**Note:** For instructions on building from source _without_ Docker, see the _[Building from source](#building-from-source)_ section, above, for further information.

Once you have [cloned this repository](#cloning-this-repository), you can run the following:

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
...
```

Or you can build for each of the targets in turn:

```
$ Resources/Docker/build all
...
```

The `prepare` operand creates base images for each of the targets (whose `Dockerfile`s can be found in
[`Resources/Docker/*`](Resources/Docker)), and is invoked automatically as part of a build, but you can run it manually
if you wish:

```
$ Resources/Docker/build prepare
checking for Docker image foundationkit-base:centos7... found
checking for Docker image foundationkit-base:jessie... found
checking for Docker image foundationkit-base:precise... found
checking for Docker image foundationkit-base:stretch... found
checking for Docker image foundationkit-base:trusty... found
checking for Docker image foundationkit-base:wheezy... found
checking for Docker image foundationkit-base:xenial... found
```

If you want to update your base images, you can use:

```
$ Resources/Docker/build update
...
```

Alternatively, you can update a single base image:

```
$ Resources/Docker/build update-jessie
building Docker image foundationkit-base:jessie...
Sending build context to Docker daemon  2.048kB
Step 1/7 : FROM debian:jessie
... 
```

While in use, `Resources/Docker/build` will create and use a `DockerBuild` directory. You can remove this with:

```
$ Resources/Docker/build clean
```

Alternatively, you can remove it yourself at any time a Docker build is not in progress.

### Copyright & licence

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

#### Third-party software

This project incorporates (via Git submodules), the following:

* [uriparser](https://github.com/uriparser/uriparser) by Weijia Song and Sebastian Pipping, licensed according to the terms of a [BSD-like license](https://github.com/uriparser/uriparser/blob/9037441b2acc8e4f779d5ad0388c218901c77f74/COPYING).
* [uthash](https://github.com/troydhanson/uthash) by Troy D. Hanson, licensed according to the terms of a [MIT/X11-style licence](https://github.com/troydhanson/uthash/blob/3fbec3efe5b5645852c3c123fae9b3a419c929f9/LICENSE).
* [jansson](https://github.com/akheron/jansson) by Petri Lehtinen, licensed according to the terms of a [MIX/X11-style licence](https://github.com/akheron/jansson/blob/074bb3838f83c8ed5b2ec3ec075c9405e6589214/LICENSE).
* [libxml2](https://libxml2.org) by [Daniel Veillard and the libxml2 contributors](https://github.com/GNOME/libxml2/blob/bc5a5d658320c37e206fe4e7b525b4a24466d0c6/AUTHORS), licensed according to the terms of a [MIT/X11-style licence](https://github.com/GNOME/libxml2/blob/bc5a5d658320c37e206fe4e7b525b4a24466d0c6/Copyright).

See the [`ThirdParty`](ThirdParty) directory for further details.

[travis]: https://img.shields.io/travis/TaliskerPlatform/FoundationKit.framework.svg
[licence]: https://img.shields.io/badge/license-Apache%202.0-blue.svg
[language]: https://img.shields.io/badge/implemented%20in-C++-yellow.svg
