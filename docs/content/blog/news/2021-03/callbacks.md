---
date: 2021-03-30
title: "Implementing delays in Cyanobyte through a callback mechanism"
linkTitle: "Implementing delays in Cyanobyte through a callback mechanism"
description: "For the BMP180 temperature/pressure sensor, a small delay needs to added after getting the temperature before the pressure can be calculated accurately."
author: Nick Felker
---

<small>This article was cross-posted [from Medium](https://medium.com/@fleker/15d16c7901ec)</small>

<img src="https://cdn-images-1.medium.com/max/1400/1*B6We_hYPlRQLMlsRjIgDtQ.png" alt="Cyanobyte Logo" />
<br>
<small>Cyanobyte Logo</small>

Over the past few years I've continued to iterate on this idea I've had for a while. When building applications for embedded devices, you've often need to connect to a peripheral using something like I2C. This requires you to either look for an existing library for that device on your platform, or write the library yourself from scratch.

For embedded software this is often an exercise in frustration, having to read through convoluted datasheets or cherry-picking from manufacturer sample code.

[Cyanobyte](https://github.com/google/cyanobyte/) was created to define a common spec for peripherals in a machine-readable format which could then be converted into platform-specific code through a code generator. Since the start, I've defined a number of peripherals in the format and support a number of platforms including Raspberry Pi, Arduino, Espruino (JavaScript), a generic C platform, and several documentation templates.

<img src="https://cdn-images-1.medium.com/max/1400/1*DkJMoiFOTuMvzIK-rA5qHw.png" />
<br>
<small>Directory listing of all template files</small>

Normally this is not the best way to create a product. You are supposed to start with one instance and polish that before moving onto the next thing. However, in my case I intentionally added support for a number of disparate platforms.

Embedded platforms are all different, and in order to verify the Cyanobyte spec would actually work for developers I had to try out a number of different platforms.

When I started out, I used the Raspberry Pi and Python. When moving to Arduino, suddenly everything had to be properly typed. Ensuring that type-safety was in the spec was critical to creating something that would gain wider adoption.

<hr>

In particular this brings me around to delays, another implementation detail that actually has significant platform differences. For the BMP180 temperature/pressure sensor, a small delay needs to added after getting the temperature before the pressure can be calculated accurately.

On the Raspberry Pi and Arduino, for example, they have blocking delay functions. It would be all too easy for me to add a simple delay step in the larger list of logical operations:

<script src="https://gist.github.com/Fleker/0b27611aaa40c8dfce51d941d6026910.js"></script>

This would result in blocking Arduino code:

<script src="https://gist.github.com/Fleker/1a9cbd08317453b5e8decca1e8e10730.js"></script>

And everything would've been fine.

However, because there are a number of additional platforms I am unable to make this assumption and spec definition. Not every platform supports blocking delays nor do they want to.

Some embedded platforms will use a task scheduler so that they can move on to another computation while they wait. Some platforms support multiple threads or cores and will need to use asynchronous logic instead.

With the concept of callbacks in mind, I had to update the spec. This would place subsequent logic into a subarray and label the delay to use in callback names:

<script src="https://gist.github.com/Fleker/d10edaff74f58971ee66ac85764ec1c1.js"></script>

This change has no bearing on Arduino, as it keeps its blocking delay. However, now we can use this to define callbacks for the [Espruino platform](https://www.espruino.com/) with JavaScript, which uses [the `setTimeout` function](https://www.espruino.com/Arduino+Differences) for delays.

So my logic now needs to accept a callback method as a function parameter and then execute it rather than returning a value directly:

<script src="https://gist.github.com/Fleker/8094eb6f1607f0805b5efbf6190865f2.js"></script>

This output would have been lot more difficult to generate had the delay remained blocking, and would've made certain types of actions like multi-threading essentially infeasible. This additional flexibility will be useful for advanced use-cases without having to refactor this in the future.

<hr>

There is another template that gave me additional trouble, which was the generic embedded C files. Rather than mandating a certain platform or library for I2C writes and reads, this uses function pointers for read/write operations. It makes the function headers a bit more complex, but gives you flexibility that doesn't exist in a strict Arduino template.

<script src="https://gist.github.com/Fleker/62f4fdeb077bc5601761435ea7f7831f.js"></script>

This flexibility means that delays cannot be assumed to be available. Perhaps you would have your own task scheduler. So it seemed like the best approach was to return the `after` field as a function pointer and you would be responsible for the delay:

<script src="https://gist.github.com/Fleker/6896ea7e59c535cee6804db4578eb721.js"></script>

I committed this code and thought for a minute. The pointers in pointers is still convoluted, but seemed reasonable enough. However, I discovered an even larger flaw in the behavior of this code.

You see, my `_callback_celsius` function needs to calculate `rawComp` based on the `temperature` variable. However, now that we are in a separate function all of our previous scoped variables are not accessible. `temperature` no longer exists and we cannot go back and get it.

What could I do? Well, what if I required you to re-enter all of the variables in the correct order? A bit onerous:

<script src="https://gist.github.com/Fleker/41507a7ee895b77bec487c9a9540fc79.js"></script>

But there also is still no way for you to know the value of `temperature`. It is an internal value to this auto-generated function.

I ended up deciding the best way was to define a struct that represented the function's state and then return that instead of a callback directly:

<script src="https://gist.github.com/Fleker/02440fc6c9e0e31c099b87adbe5ea181.js"></script>

<script src="https://gist.github.com/Fleker/5d5ef6395a18e9f17dfddf2512212493.js"></script>

Finally I had managed to get every platform to meet expectations and I merged [the pull request](https://github.com/google/cyanobyte/pull/258/files). It took some time, and the implementation may still not be perfect, but it will be satisfactory for the BMP180.

What is the moral of this blog post? Callbacks are hard. Blocking code will always be easier to write, but may end up preventing you from advanced use-cases.

For Cyanobyte, the effort to try doing too much has had trade-offs. Now that the project has continued to evolve, some of those seams have become more obvious. But it also has allowed me to better design a spec that will work for the most developers. It will save me time going forward and developer frustration as they need to perform refactors.

You can visit the project on GitHub at https://github.com/google/cyanobyte/ which has instructions on how to download the toolchain and get started building your own peripheral drivers.
