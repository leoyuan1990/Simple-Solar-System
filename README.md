# Simple-Solar-System
A simple, mostly to scale model of our solar system done in C++ using OpenGL. A better version will be uploaded soon with focus on improving the UI and visual appeal.

Click the window to begin. Start orbiting the planets by holding 'a' or 'd'. Zooming in and out are possible by holding 'w' or 's' keys respectively. Speed up or slow down the orbital speeds by holding 'z' or 'c' respectively. Right click to bring up the quick zoom and quick speed menus. You can also quit the program by pressing q.

--- CHANGES ---

1) Added an asteroid belt! Currently there is an issue with flickering since to "spice things up" the asteroids are generated in layers and randomly spaced apart. This means that random asteroids are being drawn in random locations at 60 FPS whlie the planets and sun don't flicker because they are being drawn in the same location.

2) Adjusted scaling for visual appeal. The size of the planets (although to scale relative to each other) are not to scale relative to the distances from the sun (which are to scale relative to each other). It would be impossible for this model to be fully to scale with the rendering limitations of open GL and due to the astronomical distances.

3) The user used to have to hold the up and down arrow keys to zoom in and out. This didn't make sense since it required two hands. It has now been changed to 'w' and 's' so that the user can zoom and control the planetery orbits using one hand.

4) Added Pluto! Not technically a planet but it was when I was watching Magic School Bus and that was the inspiration for this project in the first place so it would be criminal to not include it. Currently working on making the orbit elliptical.

5) Removed useless code, added useful comments.
