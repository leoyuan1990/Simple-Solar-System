# Simple-Solar-System
A simple, mostly to scale model of our solar system done in C++ using OpenGL. A better version will be uploaded soon with focus on improving the UI and visual appeal.

Click the window to begin. Start orbiting the planets by holding 'a' or 'd'. Zooming in and out are possible by holding the 'w' and 's' arrow keys respectively. Right click to bring up the quick zoom menu. You can also quit the program by pressing q.

--- UPDATE ---

1) Asteroid belt added. Currently working on a fix for the flickering which is caused by a different randomly generated asteroid locations being redrawn at 60 FPS while planets and the sun don't flicker because they are being redrawn at 60 FPS in the same location.

2) Adjusted scaling for visual appeal. The size of the planets (although to scale relative to each other) are not to scale relative to the distances from the sun (which are to scale). It would be impossible for this model to be fully to scale with the rendering limitations of open GL.

3) The user used to have to hold the up and down arrow keys to zoom in and out. This didn't make sense since it required two hands. It has now been changed to 'w' and 's' so that the user can zoom and control the planetery orbits using one hand.

4) Removed useless code, added useful comments.
