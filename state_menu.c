#include "state_menu.h"

void draw_menu_frame()
{
    set_color(RED);

    int i;

    for (i = 0; i <= SCREEN_WIDTH; ++i)
    {
        goto_xy(i, 0);
        putchar(FRAME);

        goto_xy(i, SCREEN_HEIGHT);
        putchar(FRAME);
    }

    for (i = 0; i <= SCREEN_HEIGHT; ++i)
    {
        goto_xy(0, i);
        putchar(FRAME);

        goto_xy(SCREEN_WIDTH, i);
        putchar(FRAME);
    }

    goto_xy(0, 0);
}

void draw_menu_title()
{
    set_color(GREEN);

    goto_xy(10, 2); printf("       _______..__   __.      ___       __  ___  _______   ");
    goto_xy(10, 3); printf("      /       ||  \\ |  |     /   \\     |  |/  / |   ____|  ");
    goto_xy(10, 4); printf("     |   (----`|   \\|  |    /  ^  \\    |  '  /  |  |__     ");
    goto_xy(10, 5); printf("      \\   \\    |  . `  |   /  /_\\  \\   |    <   |   __|    ");
    goto_xy(10, 6); printf("  .----)   |   |  |\\   |  /  _____  \\  |  .  \\  |  |____   ");
    goto_xy(10, 7); printf("  |_______/    |__| \\__| /__/     \\__\\ |__|\\__\\ |_______|  ");
}

void menu_items()
{
    set_color(WHITE);

    goto_xy(35, 11); printf("New Game");
    goto_xy(35, 13); printf("Settings");
    goto_xy(35, 15); printf("Quit Game");
}

void state_menu()
{
    int item = 11;

    clear_screen();
    draw_menu_frame();
    draw_menu_title();
    menu_items();

    goto_xy(31, item);
    printf("-->");

    goto_xy(3, 22);
    printf("Press <RETURN> to select an item...");

    while (true)
    {
        if (key_hit())
        {
            KeyButton key = get_key();

            if (key == KEY_UP || key == KEY_W)
            {
                if (item >= 13)
                {
                    goto_xy(31, item);
                    printf("   ");
                    item -= 2;
                    goto_xy(31, item);
                    printf("-->");
                }
            }
            else if (key == KEY_DOWN || key == KEY_S)
            {
                if (item <= 13)
                {
                    goto_xy(31, item);
                    printf("   ");
                    item += 2;
                    goto_xy(31, item);
                    printf("-->");
                }
            }
            else if (key == KEY_ENTER)
            {
                switch (item)
                {
                    case 11: settings.current_state = PLAY; return;
                    case 13: settings.current_state = SETTINGS; return;
                    case 15: settings.running = false; return;
                }
            }

            goto_xy(38, 22);
        }
    }
}
