---
title: "Draft Specifications"
linkTitle: "Draft Specifications"
weight: 1
description: >
  What is in draft?
---

Visit the [Cyanobyte Pull Requests](https://github.com/google/cyanobyte/pulls) to see all of the
pull requests for the repository.

This directory will host any active Cyanobyte specs, along with [a GitHub issue](https://github.com/google/cyanobyte/issues/)
which can be used for discussion.

<script>
// Automatically append GitHub issues marked as 'for-review'
const url = "https://api.github.com/repos/google/cyanobyte/issues?state=open&labels=for-review";

window.onload = () => {
    fetch(url)
    .then((response) => {
        return response.json();
    })
    .then((data) => {
        const div = document.querySelector('.section-index')
        const bullets = data.map(datum =>
            `<li><a href="${datum.html_url}">${datum.title}</a></li>`
        )
        const html = `<ul>${bullets.join('')}</ul>`
        div.innerHTML += html
    });
};
</script>