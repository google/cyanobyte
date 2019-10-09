---
title: "Generate These Docs"
linkTitle: "Generate These Docs"
weight: 99
description: >
  How do we build this site?
---

Cyanobyte's devsite uses [Docsy](https://www.docsy.dev/) as the theme, with Hugo as the underlying
engine.

I recommend following the [Docsy Getting Started guide](https://www.docsy.dev/docs/getting-started/) to know how to get started.

Make sure the theme is setup with `git submodule update --init --recursive`

Run `cd public && hugo serve` to serve at http://localhost:1313.

Run `hugo && firebase deploy` to generate and deploy the site.
  If not done before, you may need to run `npm install postcss-cli autoprefixer`