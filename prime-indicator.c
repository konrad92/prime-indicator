
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>

#define PRIME_INDICATOR_VERSION "0.1.1"

#define _(String) gettext(String)

struct {
    AppIndicator *indicator;
    GtkMenu *menu;
} app;

const char *icons[] = {
    "/usr/share/prime-indicator/intel.png",
    "/usr/share/prime-indicator/nvidia.png"
};

// determine specified shell argument
int findarg(int argc, char *argv[], const char *str);

// app indicator
void appInitIndicator();
void appAddMenuItem(const char *label, GCallback activate);
void appAddMenuSeparator();

// activate events
void switchGraphicCards();
void openSettingsDialog();

// check for discrete graphic card
int checkDiscrete();

// entry point
int main(int argc, char *argv[])
{
    // show program version
    if(findarg(argc, argv, "--version")) {
        printf("PRIME indicator version \"%s\"\n", PRIME_INDICATOR_VERSION);
        return 0; // only shows program version
    }

    // locale setup
    setlocale(LC_ALL, "");
    bindtextdomain("prime-indicator", "/usr/share/locale");
    textdomain("prime-indicator");

    // gtk init
    gtk_init(&argc, &argv);

    // gtk app indicator
    appInitIndicator();
    appAddMenuItem(_("Switch graphic cards"), G_CALLBACK(switchGraphicCards));
    appAddMenuSeparator();
    appAddMenuItem(_("Open settings"), G_CALLBACK(openSettingsDialog));

    if(findarg(argc, argv, "--with-quit")) {
        appAddMenuItem(_("Quit"), G_CALLBACK(gtk_main_quit));
    }

    // gtk mainloop
    gtk_main();

    return 0;
}

int findarg(int argc, char *argv[], const char *str)
{
    while(--argc) {
        if(strcmp(*++argv, str) == 0) {
            return 1;
        }
    }

    return 0;
}

void appInitIndicator()
{
    const char *icon = icons[0];

    if(checkDiscrete()) {
        icon = icons[1];
    }

    // create app indicator widget
    app.indicator = app_indicator_new(
        "prime-indicator",
        icon,
        APP_INDICATOR_CATEGORY_APPLICATION_STATUS
    );

    app_indicator_set_status(app.indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_attention_icon(app.indicator, "indicator-messages-new");

    // initialize menus
    app.menu = GTK_MENU(gtk_menu_new());
    app_indicator_set_menu(app.indicator, app.menu);
}

void appAddMenuItem(const char *label, GCallback activate)
{
    GtkWidget *child = gtk_menu_item_new_with_label(label);

    if(activate) {
        g_signal_connect(G_OBJECT(child), "activate", activate, 0);
    }
    
    gtk_widget_show(child);
    gtk_menu_append(app.menu, child);
}

void appAddMenuSeparator()
{
    GtkWidget *child = gtk_separator_menu_item_new();

    gtk_widget_show(child);
    gtk_menu_append(app.menu, child);
}

void switchGraphicCards()
{
    system("/usr/lib/prime-indicator/switchgpu");
}

void openSettingsDialog()
{
    system("nvidia-settings &");
}

int checkDiscrete()
{
    char card = 0;

    FILE *p = popen("prime-select query", "r");
    fread(&card, 1, 1, p);
    pclose(p);

    return (card == 'n');
}
