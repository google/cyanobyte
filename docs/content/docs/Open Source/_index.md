---
title: "How to Contribute"
linkTitle: "How to Contribute"
weight: 97
description: >
  How do I get involved?
---

# How to Contribute

We'd love to accept your patches and contributions to this project. There are
just a few small guidelines you need to follow.

## Contributor License Agreement

Contributions to this project must be accompanied by a Contributor License
Agreement. You (or your employer) retain the copyright to your contribution;
this simply gives us permission to use and redistribute your contributions as
part of the project. Head over to <https://cla.developers.google.com/> to see
your current agreements on file or to sign a new one.

You generally only need to submit a CLA once, so if you've already submitted one
(even if it was for a different project), you probably don't need to do it
again.

## Code reviews

All submissions, including submissions by project members, require review. We
use GitHub pull requests for this purpose. Consult
[GitHub Help](https://help.github.com/articles/about-pull-requests/) for more
information on using pull requests.

## Contributing new drivers
We welcome new drivers that may help identify holes in the current specification.
If you are adding a new driver, please ensure:

1. Your driver works on all available templates in the repository
1. Your driver passes the the validation tool
1. There are tests which verify the rendered output

## Contributing new platforms
We welcome new templates for new languages and platforms, which may help identify
holes in the current specification. If you are adding a new template, please ensure:

1. The output code for each driver compiles on your platform
1. Your template works on the hardware you specify for all available drivers in the
repository
1. There are tests which verify the rendered output