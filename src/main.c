#include <SFML/Audio.h>
#include <SFML/Graphics.h>

int main()
{
  sfVideoMode mode = {800, 600, 32};
  sfRenderWindow *window;

  /* Create the main window */
  window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
  if (!window)
    return 1;

  /* Start the game loop */
  while (sfRenderWindow_isOpen(window))
  {

    /* Clear the screen */
    sfRenderWindow_clear(window, sfBlack);

    /* Update the window */
    sfRenderWindow_display(window);
  }

  sfRenderWindow_destroy(window);

  return 0;
}