---
title: "Run lint"
linkTitle: "Run lint"
weight: 3
description: >
  Make sure to run linting before you submit a PR
---

This requires pylint.

`python3 -m pylint --rcfile=test/pylintrc src/*.py python3 -m pylint --rcfile=test/pylintrc test/sampleData/*.py`