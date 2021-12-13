#include "state_play.h"

void draw_frame()
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

    for (i = 0; i <= BOARD_WIDTH; ++i)
    {
        goto_xy(i, BOARD_HEIGHT);
        putchar(FRAME);
    }

    goto_xy(0, 0);
}

void draw_food(point f)
{
    set_color(BLUE);

    goto_xy(f.x, f.y);

    putchar(FOOD);
}

void display_score(int score)
{
    set_color(BLUE);

    goto_xy(62, 22);

    printf("SCORE: %3d", score);
}

void display_level(int level)
{
    set_color(RED);

    goto_xy(35, 22);

    printf("LEVEL: %2d", level);
}

void show_blood(point p)
{
    set_color(RED);

    goto_xy(p.x, p.y);

    putchar(SNAKE_BODY);
}

void game_over()
{
    set_color(RED);

    int i, j;
    for (i = 23; i != 56; ++i)
    {
        for (j = 8; j != 15; ++j)
        {
            goto_xy(i, j);
            if (i == 23 || i == 55 || j == 8 || j == 14)
                putchar('*');
            else
                putchar(' ');
        }
    }

    set_color(WHITE);

    goto_xy(33, 10);
    printf("- GAME OVER -");

    goto_xy(25, 12);
    printf("Press <RETURN> to continue...");

    while (get_key() != KEY_ENTER)
        ;
}

bool self_collision(list* s)
{
    point head_pos = get_front(s);
    node* iterator = s->head->next;

    while (iterator != NULL)
    {
        if (equal(head_pos, iterator->item))
            return true;

        iterator = iterator->next;
    }

    return false;
}

bool wall_collision(list* s)
{
    point head_pos = get_front(s);

    return head_pos.x == 0 || head_pos.x == BOARD_WIDTH ||
           head_pos.y == 0 || head_pos.y == BOARD_HEIGHT;
}

bool food_collision(list* s, point f)
{
    point head_pos = get_front(s);

    return equal(head_pos, f);
}

point generate_food(list* s)
{
    point ret;

    ret.x = rand() % 78 + 1;
    ret.y = rand() % 19 + 1;

    node* iterator = s->head;

    while (iterator != NULL)
    {
        if (equal(ret, iterator->item))
        {
            ret.x = rand() % 78 + 1;
            ret.y = rand() % 19 + 1;

            iterator = s->head;
        }
        else
        {
            iterator = iterator->next;
        }
    }

    return ret;
}

void process_events(snake_direction* d)
{
    KeyButton key = get_key();

    if ((key == KEY_W || key == KEY_UP) && *d != DOWN)
        *d = UP;
    else if ((key == KEY_S || key == KEY_DOWN) && *d != UP)
        *d = DOWN;
    else if ((key == KEY_A || key == KEY_LEFT) && *d != RIGHT)
        *d = LEFT;
    else if ((key == KEY_D || key == KEY_RIGHT) && *d != LEFT)
        *d = RIGHT;
    else if (key == KEY_ESC)
    {
        set_color(WHITE);
        goto_xy(5, 22);
        printf("PAUSE <ESC>...");

        while (get_key() != KEY_ESC)
            ;

        goto_xy(5, 22);
        printf("              ");
    }
}

void move_and_grow_snake(list* s, snake_direction d, bool* grow_snake)
{
    set_color(GREEN);

    point head_pos = get_front(s);

    switch (d)
    {
        case    UP: --head_pos.y; break;
        case  DOWN: ++head_pos.y; break;
        case  LEFT: --head_pos.x; break;
        case RIGHT: ++head_pos.x; break;
    }

    goto_xy(head_pos.x, head_pos.y);
    putchar(SNAKE_BODY);
    push_front(s, head_pos);

    if (*grow_snake)
    {
        *grow_snake = false;
        return;
    }

    point tail_pos = get_back(s);

    if (!equal(head_pos, tail_pos))
    {
        goto_xy(tail_pos.x, tail_pos.y);
        putchar(' ');
    }

    pop_back(s);
}

void change_level(int* level, int* score)
{
    if (*score == 5 && *level == 1)
        *level = 2;
    else if (*score == 10 && *level == 2)
        *level = 3;
    else if (*score == 15 && *level == 3)
        *level = 4;
    else if (*score == 30 && *level == 4)
        *level = 5;
    else if (*score == 45 && *level == 5)
        *level = 6;
    else if (*score == 60 && *level == 6)
        *level = 7;
    else if (*score == 80 && *level == 7)
        *level = 8;
    else if (*score == 100 && *level == 8)
        *level = 9;
    else if (*score == 150 && *level == 9)
        *level = 10;

    display_level(*level);
}

void state_play()
{
    list snake;
    snake_direction direction = START_DIRECTION;
    point food;
    point position = {SNAKE_START_POS_X, SNAKE_START_POS_Y};
    bool food_eaten = false;
    bool grow_snake = false;
    int score = 0;
    int counter = 0;
    int level = settings.start_level;

    clear_screen();

    init_list(&snake);
    push_back(&snake, position);

    food = generate_food(&snake);
    draw_food(food);

    draw_frame();
    display_score(score);

    while (true)
    {
        ++counter;

        if (counter < settings.start_length)
            grow_snake = true;

        if (food_eaten)
        {
            food = generate_food(&snake);
            draw_food(food);
            food_eaten = false;
        }

        if (key_hit())
            process_events(&direction);

        move_and_grow_snake(&snake, direction, &grow_snake);

        if (food_collision(&snake, food))
        {
            food_eaten = true;
            grow_snake = true;
            ++score;
            display_score(score);
        }

        change_level(&level, &score);

        if (wall_collision(&snake) || self_collision(&snake))
        {
            show_blood(get_front(&snake));
            break;
        }

        delay(100 - 4 * level);
    }

    game_over();
    settings.current_state = MENU;
    clear_list(&snake);
}
