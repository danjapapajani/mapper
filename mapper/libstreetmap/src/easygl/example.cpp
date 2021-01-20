#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <vector>
#include <string>
#include "graphics.h"

// Callbacks for event-driven window handling.
void drawscreen(void);
void act_on_new_button_func(void (*drawscreen_ptr) (void));
void act_on_button_press(float x, float y, t_event_buttonPressed event);
void act_on_mouse_move(float x, float y);
void act_on_key_press(char c, int keysym);

// A handy delay function for the animation example
void delay(long milliseconds);

// State variables for the example showing entering lines and rubber banding
// and the new button example.
static bool line_entering_demo = false;
static bool have_rubber_line = false;
static t_point rubber_pt; // Last point to which we rubber-banded.
static std::vector<t_point> line_pts; // Stores the points entered by user clicks.
static int num_new_button_clicks = 0;


// You can use any coordinate system you want.
// The coordinate system below matches what you have probably seen in math 
// (ie. with origin in bottom left).
// Note, that text orientation is not affected. Zero degrees will always be the normal, readable, orientation.
const t_bound_box initial_coords = t_bound_box(0, 0, 1100, 1150);



/**/

int main() {
    
    std::cout << "About to start graphics.\n";

    /**************** initialize display **********************/


    // Set the name of the window (in UTF-8), with white background.
    init_graphics("Some Example Graphics", WHITE); // you could pass a t_color RGB triplet instead

    // We'll first do double buffered drawing, where we draw to an off-screen
    // buffer and then quickly copy it to the screen to avoid flashes as we 
    // rapidly change the graphics when panning or zooming
    set_drawing_buffer(OFF_SCREEN);

    // Set-up coordinates. The coordinates passed in define what coordinate
    // limits you want to use; this coordinate system is mapped to fill 
    // the screen.
    set_visible_world(initial_coords);

    // Set the message at the bottom (also UTF-8)
    update_message("Interactive graphics example with double buffering.");

    // Pass control to the window handling routine.  It will watch for user input
    // and redraw the screen / pan / zoom / etc. the graphics in response to user
    // input or windows being moved around the screen.  We have to pass in 
    // at least one callback -- the one to redraw the graphics.
    // Three other callbacks can be provided to handle mouse button presses,
    // mouse movement and keyboard button presses in the graphics area, 
    // respectively. Those 3 callbacks are optional, so we can pass NULL if
    // we don't need to take any action on those events, and we do that
    // below.
    // This function will return if and when
    // the user presses the proceed button.

    event_loop(NULL, NULL, NULL, drawscreen);
    
    t_bound_box old_coords = get_visible_world(); // save the current view for later;

    
    /******************* animation section *******************************/
    // User might have panned and zoomed, which changes what world 
    // coordinates are visible on the screen. Get back to a known view.
    set_visible_world(initial_coords);
    
    // We're going to draw some lines and want them to immediately appear 
    // on the screen, so we'll turn off double-buffering for this example
    set_drawing_buffer(ON_SCREEN);
    clearscreen();
    update_message("Non-interactive (animation) graphics, without double buffering.");
    setcolor(RED);
    setlinewidth(1);
    setlinestyle(DASHED);

    t_point start_point = t_point(100, 0);
    for (int i = 0; i < 50; i++) {
        drawline(start_point, start_point + t_point(500, 10));
        flushinput();
        delay(50);
        start_point += t_point(5, 10);
    }

    
    /**** Draw an interactive still picture again.  I'm also creating one new button. ****
     * This time we'll draw without double buffering, so you can see the difference 
     * and so we can do fast "rubber banding" with XOR drawing mode.
     */

    update_message("Interactive graphics without double buffering. Click in graphics area to rubber band line.");
    create_button("Window", "0 Clicks", act_on_new_button_func); // name is UTF-8

    // Enable mouse movement (not just button presses) and key board input.
    // The appropriate callbacks will be called by event_loop.
    set_keypress_input(true);
    set_mouse_move_input(true);
    line_entering_demo = true;

    // draw the screen once before calling event loop, so the picture is correct 
    // before we get user input.
    set_visible_world(old_coords); // restore saved coords -- this takes us back to where the user panned/zoomed.

    drawscreen();

    // Call event_loop again so we get interactive graphics again.
    // This time pass in all the optional callbacks so we can take
    // action on mouse buttons presses, mouse movement, and keyboard
    // key presses.
    event_loop(act_on_button_press, act_on_mouse_move, act_on_key_press, drawscreen);

    close_graphics();
    std::cout << "Graphics closed down.\n";
    
    
    // Test we can re-open a graphics window
    init_graphics("Re-opened window", WHITE);
    set_drawing_buffer(OFF_SCREEN);
    set_visible_world(initial_coords);
    update_message ("I have re-opened the window!");
    event_loop(NULL, NULL, NULL, drawscreen);
    close_graphics();
    std::cout << "Graphics closed again.  Really done now!\n";

    return (0);
}


void drawscreen(void) {

    /* The redrawing routine for still pictures.  The graphics package calls  
     * this routine to do redrawing after the user changes the window 
     * in any way.                                                    
     */

    set_draw_mode(DRAW_NORMAL); // Should set this if your program does any XOR drawing in callbacks.
    clearscreen(); /* Should precede drawing for all drawscreens */

    setfontsize(10);
    setlinestyle(SOLID);
    setlinewidth(1);
    setcolor(BLACK);

    {
        /**************
         * Draw some rectangles using the indexed colours
         **************/

        color_types color_indicies[] = {
            LIGHTGREY,
            DARKGREY,
            WHITE,
            BLACK,
            BLUE,
            GREEN,
            YELLOW,
            CYAN,
            RED,
            DARKGREEN,
            MAGENTA
        };

        const float rectangle_width = 50;
        const float rectangle_height = rectangle_width;
        const t_point start_point = t_point(150, 30);
        t_bound_box color_rectangle = t_bound_box(start_point, rectangle_width, rectangle_height);

        // text is UTF-8
        drawtext(110, color_rectangle.get_ycenter(), "colors", 2 * (start_point.x - 110), rectangle_height);

        for (size_t i = 0; i < sizeof (color_indicies) / sizeof (color_indicies[0]); ++i) {
            setcolor(color_indicies[i]);
            fillrect(color_rectangle);
            color_rectangle += t_point(rectangle_width, 0);
        }

        drawtext(400, color_rectangle.get_ycenter(), "fillrect", FLT_MAX, rectangle_height);

        /********
         * Draw some rectangles with RGB triplet colours
         ********/

        std::srand( time(0)); // hack to make the colors change once per second.

        for (size_t i = 0; i < 3; ++i) {
            color_rectangle += t_point(rectangle_width, 0);
            setcolor(std::rand(), std::rand(), std::rand()); // note that setcolor(..) also takes a t_color object.
            fillrect(color_rectangle);
        }

        setcolor(BLACK);
        drawrect(start_point, color_rectangle.top_right());

    }

    /********
     * Draw some example lines, shapes, and arcs
     ********/
    {
        float radius = 50;

        setcolor(BLACK);
        drawtext(250, 150, "drawline", 150.0, FLT_MAX);
        setlinestyle(SOLID);
        drawline(200, 120, 200, 200);
        setlinestyle(DASHED);
        drawline(300, 120, 300, 200);

        setcolor(MAGENTA);
        drawtext(450, 160, "drawellipticarc", 150, FLT_MAX);
        drawellipticarc(550, 160, 30, 60, 90, 270);
        t_point cen(800, 160);
        drawtext(720, 160, "fillellipticarc", 150, FLT_MAX);
        fillellipticarc(cen, 30, 60, 90, 270);

        setcolor(BLUE);
        drawtext(190, 300, "drawarc", radius * 2, 150);
        drawarc(190, 300, radius, 0, 270);
        drawarc(300, 300, radius, 0, -180);
        fillarc(410, 300, radius, 90, -90);
        fillarc(520, 300, radius, 0, 360);
        setcolor(BLACK);
        drawtext(520, 300, "fillarc", radius * 2, 150);
        setcolor(BLUE);
        fillarc(630, 300, radius, 90, 180);
        fillarc(740, 300, radius, 90, 270);
        fillarc(850, 300, radius, 90, 30);
    }

    /********
     * Draw some rotated text
     ********/

    {
        const float textsquare_width = 200;

        t_bound_box textsquare = t_bound_box(t_point(100, 400), textsquare_width, textsquare_width);

        setcolor(BLUE);
        drawrect(textsquare);

        setcolor(GREEN);
        drawrect(textsquare.get_center(), textsquare.top_right());
        drawrect(textsquare.bottom_left(), textsquare.get_center());

        setcolor(RED);
        drawline(textsquare.bottom_left(), textsquare.top_right());
        drawline(textsquare.left(), textsquare.top(), textsquare.right(), textsquare.bottom());

        setcolor(t_color(0, 0, 0, 100));
        settextattrs(14, 0); // set a reasonable font size, and zero rotation.
        drawtext(textsquare.get_xcenter(), textsquare.bottom(), "0 degrees", textsquare.get_width(), textsquare.get_height());
        settextrotation(90);
        drawtext(textsquare.right(), textsquare.get_ycenter(), "90 degrees", textsquare.get_width(), textsquare.get_height());
        settextrotation(180);
        drawtext(textsquare.get_xcenter(), textsquare.top(), "180 degrees", textsquare.get_width(), textsquare.get_height());
        settextrotation(270);
        drawtext(textsquare.left(), textsquare.get_ycenter(), "270 degrees", textsquare.get_width(), textsquare.get_height());

        settextrotation(45);
        drawtext(textsquare.get_center(), "45 degrees", textsquare.get_width(), textsquare.get_height());
        settextrotation(135);
        drawtext(textsquare.get_center(), "135 degrees", textsquare.get_width(), textsquare.get_height());

        // It is probably a good idea to set text rotation back to zero,
        // as this is the way most text will be drawn, and you dont't want
        // to have to set it to zero every time you draw text. However,
        // there are checks in the easygl graphics that make it a no-op to set the text size, or
        // rotation, to the current value so there isn't a lot of speed hit to setting it all the time.
        settextrotation(0);
    }

    /*******
     * Draw some polygons
     *******/

    {
        t_point polypts[3] = {
            {500, 400},
            {440, 480},
            {560, 480}};
        t_point polypts2[4] = {
            {700, 400},
            {650, 480},
            {750, 480},
            {800, 400}};

        setfontsize(10);
        setcolor(RED);
        fillpoly(polypts, 3);
        fillpoly(polypts2, 4);
        setcolor(BLACK);
        drawtext(500, 450, "fillpoly1", 80);
        drawtext(725, 440, "fillpoly2", 100.0);
        setcolor(DARKGREEN);
        setlinestyle(SOLID);
        t_bound_box rect = t_bound_box(350, 550, 650, 670);
        drawtext_in(rect, "drawrect");
        drawrect(rect);
    }
    
    /*********
     * Draw some semi-transparent primitives, and wide lines with different
     * end shapes.
     *********/
    {
        setfontsize(10);

        // Different lines
        for (int i = 0; i <= 2; ++i)
        {
            int offsetY = 50*i;
            if (i == 0) {
               setcolor (BLACK);
               setlinestyle (SOLID); // Butt ends are the default
               drawtext (1100, 920+offsetY, "Butt ends, opaque", 400); // Don't draw if more than 400 world coords wide
            } else if (i == 1) {
                setlinestyle(SOLID, ROUND); // Round ends for lines
                setcolor(t_color(0, 255, 0, 255*2/3)); // Green line that is opaque (0% transparent)
                drawtext (1100, 920+offsetY, "Round ends, 33% transparent", 400);
            } 
            else {
                setlinestyle(DASHED, BUTT); // Flat ends for lines
                setcolor(t_color(255, 0, 0, 255/3));  // Red line that is 67% transparent
                drawtext (1100, 920+offsetY, "Butt ends, 67% transparent", 400);
            }
            drawtext(200, 900+offsetY, "Thin line (width 1)", 200.0, FLT_MAX);
            setlinewidth(1);
            drawline(100, 920+offsetY, 300, 920+offsetY);
            drawtext(500, 900+offsetY, "Width 3 Line", 200.0, FLT_MAX);
            setlinewidth(3);
            drawline(400, 920+offsetY, 600, 920+offsetY);
            drawtext(800, 900+offsetY, "Width 6 Line", 200.0, FLT_MAX);
            setlinewidth(6);
            drawline(700, 920+offsetY, 900, 920+offsetY);
        }
        
        // Transparent rectangles using fillrect
        setcolor(t_color(255, 0, 0, 255));
        fillrect(1000, 400, 1050, 800);
        setcolor(t_color(0, 0, 255, 255));
        fillrect(1000+50, 400, 1050+50, 800);
        setcolor(t_color(0, 255, 0, 255/2));  // 50% transparent
        fillrect(1000+25, 400-100, 1050+25, 800-200);
        setcolor (BLACK);
        settextrotation (90);
        drawtext (1000 - 50, 500, "Partially transparent polys", 500);
        settextrotation (0);
        
        // Semi-transparent Polygons
        t_point polypts[4] = {
            {465, 380},
            {400, 450},
            {765, 450},
            {850, 380}};
        t_point polypts2[3] = {
            {550, 420},
            {475, 500},
            {875, 500}};
        setcolor(t_color(255, 100, 255, 255/2));
        fillpoly(polypts, 4);
        setcolor(t_color(100, 100, 255, 255/3));
        fillpoly(polypts2, 3);
        
        setlinewidth(1);
    }

    /*********
     * Do some things in screen coordinates. (0,0) is the top-left corner 
     * of the window, and these coordinates are not transformed so the object
     * will not pan or zoom.
     *********/
    {
        set_coordinate_system(GL_SCREEN);
        setcolor(t_color(255, 0, 0));
        setlinestyle(SOLID);
        drawrect (10, 10, 100, 100);
        // Specifying FLT_MAX for the size limits on the text (in world coordinates) so
        // it will always be drawn.
        drawtext (55, 33, "Screen coord");
        drawtext (55, 66, "Fixed loc");
        set_coordinate_system(GL_WORLD);
    }
    
    /*********
     * Draw some example text, with the bounding box functions
     *********/

    {
        const float text_example_width = 800;

        const int num_lines = 2;
        const int max_strings_per_line = 3;

        const int num_strings_per_line[num_lines] = {3, 2};

        // Text is UTF-8, so you can use special characters, as long as your font supports them.
        const char* const line_text[num_lines][max_strings_per_line] = {
            {
                "8 Point Text",
                "12 Point Text",
                "18 Point Text"
            },
            {
                "24 Point Text",
                "32 Point Text"
            }
        };

        const int text_sizes[num_lines][max_strings_per_line] = {
            {8, 12, 15},
            {24, 32}
        };

        setcolor(BLACK);
        setlinestyle(DASHED);

        for (int i = 0; i < num_lines; ++i) {
            t_bound_box text_bbox = t_bound_box(t_point(100., 710. + i * 60.), text_example_width / num_strings_per_line[i], 60.);
            for (int j = 0; j < num_strings_per_line[i]; ++j) {
                setfontsize(text_sizes[i][j]);
                drawtext_in(text_bbox, line_text[i][j]);
                drawrect(text_bbox);

                text_bbox += t_point(text_example_width / num_strings_per_line[i], 0);
            }
        }
    }

    /********
     * Draw the rubber-band line, if it's there
     ********/

    setlinewidth(1);
    setcolor(GREEN);
    setlinestyle (SOLID);

    for (unsigned int i = 1; i < line_pts.size(); i++)
        drawline(line_pts[i - 1], line_pts[i]);

    // Screen redraw will get rid of a rubber line.  
    have_rubber_line = false;

    /********
     * Draw a small png
     ********/
    draw_surface(load_png_from_file("small_image.png"), 50, 200);
    setfontsize (10);
    setcolor (BLACK);
    drawtext (50, 225, "draw_surface", 200);

    // Need to copy the off screen buffer to screen if we're using double buffering.
    // Harmless to call this if we're not using double-buffering.
    copy_off_screen_buffer_to_screen();
}


void delay(long milliseconds) {
    // if you would like to use this function in your
    // own code you will need to #include <chrono> and
    // <thread>
    std::chrono::milliseconds duration(milliseconds);
    std::this_thread::sleep_for(duration);
}


void act_on_new_button_func(void (*drawscreen_ptr) (void)) {
// Callback function for the new button we created. This function will be called
// when the user clicks on the button. It just counts how many
// times you have clicked the button.  

    char old_button_name[200], new_button_name[200];
    std::cout << "You pressed the new button!\n";
    setcolor(MAGENTA);
    setfontsize(12);
    drawtext(500, 500, "You pressed the new button!", 10000.0, FLT_MAX);
    sprintf(old_button_name, "%d Clicks", num_new_button_clicks);
    num_new_button_clicks++;
    sprintf(new_button_name, "%d Clicks", num_new_button_clicks);
    change_button_text(old_button_name, new_button_name);

    // Re-draw the screen (a few squares are changing colour with time)
    drawscreen_ptr();
}


void act_on_button_press(float x, float y, t_event_buttonPressed event) {

    /* Called whenever event_loop gets a button press in the graphics *
     * area.  Allows the user to do whatever he/she wants with button *
     * clicks.                                                        */

    std::cout << "User clicked a mouse button at coordinates ("
            << x << "," << y << ")";
    if (event.shift_pressed || event.ctrl_pressed) {
        std::cout << " with ";
        if (event.shift_pressed) {
            std::cout << "shift ";
            if (event.ctrl_pressed)
                std::cout << "and ";
        }
        if (event.ctrl_pressed)
            std::cout << "control ";
        std::cout << "pressed.";
    }
    std::cout << std::endl;

    if (line_entering_demo) {
        line_pts.push_back(t_point(x, y));
        have_rubber_line = false;

        // Redraw screen to show the new line.  Could do incrementally, but this is easier.
        drawscreen();
    }
}

void act_on_mouse_move(float x, float y) {
    // function to handle mouse move event, the current mouse position in the current world coordinate
    // system (as defined in your call to init_world) is returned

    std::cout << "Mouse move at " << x << "," << y << ")\n";
    if (line_pts.size() > 0) {
        // Rubber banding to a previously entered point.
        // Go into XOR mode.  Make sure we set the linestyle etc. for xor mode, since it is 
        // stored in different state than normal mode.
        set_draw_mode(DRAW_XOR);
        setlinestyle(SOLID);
        setcolor(WHITE);
        setlinewidth(1);
        int ipt = line_pts.size() - 1;

        if (have_rubber_line) {
            // Erase old line.  
            drawline(line_pts[ipt], rubber_pt);
        }
        have_rubber_line = true;
        rubber_pt.x = x;
        rubber_pt.y = y;
        drawline(line_pts[ipt], rubber_pt); // Draw new line
    }
}


#include <X11/keysym.h>

void act_on_key_press(char c, int keysym) {
    // function to handle keyboard press event, the ASCII character is returned
    // along with an extended code (keysym) on X11 to represent non-ASCII
    // characters like the arrow keys.

    std::cout << "Key press: char is " << c << std::endl;

#ifdef X11 // Extended keyboard codes only supported for X11 for now
    switch (keysym) {
        case XK_Left:
            std::cout << "Left Arrow" << std::endl;
            break;
        case XK_Right:
            std::cout << "Right Arrow" << std::endl;
            break;
        case XK_Up:
            std::cout << "Up Arrow" << std::endl;
            break;
        case XK_Down:
            std::cout << "Down Arrow" << std::endl;
            break;
        default:
            std::cout << "keysym (extended code) is " << keysym << std::endl;
            break;
    }
#endif
}

