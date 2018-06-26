# Lifecycle


## Intro

The code for half of Daniel Bandfield's (me) installation 'Lifecycle'
On a TV a simulation of worm-like micro-organisms played, while a machine with an arterial system of pipes watched. When any of the worms died, the machine noticed and pumped 'blood' around its system.

This repo is the code for the simulation.

This is what it looks like:

<p><a href="https://vimeo.com/223166910">Lifecycle</a></p>

![screenshot](screenshots/1.png?raw=true "The Micro-organisms")


## Prequisites

- This code has been developed and tested for Raspberry Pi (Raspbian Stretch Lite). It has also been tested on Arch Linux and at one point on Windows (should still work).

- C++ compiler/IDE of your choice.

- OpenFrameworks Library. See the website for easy to follow installation instructions

- Make sure the binary ends up one level above bin/data so it can access the data files

## Structure

See individual files for details.

`ofApp` is where most of the action happens.\
`organism` represents an individual micro-organism. They are programmed to move around semi-randomly, except when there is something they want. This is either food or a mate. Wants are based on semi-random timers with various preqrequisites. Eventualy they will die, either through old age or hunger if they can't get food.\
`segment` represents one of the physical segments that makes up an organism\
`petri` is simply just the background.\
`food` represents the food source of the micro-organisms.\
`log` and `log-entry` are features for displaying text that were removed for aesthetic reasons.

