/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>

#include "engine.h"
#include "config.h"
#include "common.h"
#include "../about.h"
#include "../graphics/display.h"

#define TRUE_S "true"
#define FALSE_S "false"

private void generate_default_cfg(ALLEGRO_CONFIG *default_cfg);

public void application_config(void)
{
    ALLEGRO_CONFIG *default_cfg, *user_cfg;
    uint8 cfg_switch = 0;
    char *cfg_value = NULL, *cfg_value2 = NULL;
    int32 int32_var = 0;

    /* Create cfg structure for defaults */
    default_cfg = al_create_config();

    /* Generate default cfg */
    generate_default_cfg(default_cfg);

    /* Check for configuration file */

    if(cfg_switch = check_file(GLOBAL_CONFIG_NAME)) /* Must be one = */
    {
        /* Read user cfg */
        if((user_cfg = al_load_config_file(GLOBAL_CONFIG_NAME)) == NULL)
        {
            cfg_switch = 0;
            print_logs(1, "Failed to read application configuration file!");
        }
    } else {
        /* Save default cfg */
        if(!al_save_config_file(GLOBAL_CONFIG_NAME, default_cfg))
        {
            print_logs(1, "Program can not save default configuration file!");
        }
    }

    /* If cfg file exists, load it */
    if(cfg_switch)
    {
        cfg_value = (char *) al_get_config_value(user_cfg, NULL, "SKIP_CONFIRM_EXIT");
    }
    /* If cfg file exists accept only "true" or "false", else get defaults */
    if(cfg_switch ? (stricmp(cfg_value, FALSE_S) && stricmp(cfg_value, TRUE_S)) : 1)
    {
        cfg_value = (char *) al_get_config_value(default_cfg, NULL, "SKIP_CONFIRM_EXIT");
    }
    /* Write value */
    if(stricmp(cfg_value, FALSE_S)) skip_confirm_exit = 1; else skip_confirm_exit = 0;
    /* "SKIP_CONFIRM_EXIT" entry END */


    if(cfg_switch)
    {
        cfg_value = (char *) al_get_config_value(user_cfg, NULL, "SKIP_WELCOME_SCREEN");
    }
    if(cfg_switch ? (stricmp(cfg_value, FALSE_S) && stricmp(cfg_value, TRUE_S)) : 1)
    {
        cfg_value = (char *) al_get_config_value(default_cfg, NULL, "SKIP_WELCOME_SCREEN");
    }
    if(stricmp(cfg_value, FALSE_S)) skip_welcome_screen = 1; else skip_welcome_screen = 0;
    /* "SKIP_WELCOME_SCREEN" entry END */


    if(cfg_switch)
    {
        cfg_value = (char *) al_get_config_value(user_cfg, NULL, "DISPLAY_FPS");
    }
    if(!cfg_switch || !cfg_value)
    {
        cfg_value = (char *) al_get_config_value(default_cfg, NULL, "DISPLAY_FPS");
    }
    int32_var = atoi(cfg_value);
    if(int32_var > 0  &&  int32_var <= 60) /* FPS 1-60, default 45 */
    {
        display_FPS = (uint8) int32_var;
    } else {
        cfg_value = (char *) al_get_config_value(default_cfg, NULL, "DISPLAY_FPS");
        display_FPS = (uint8) atoi(cfg_value);
    }
    /* "DISPLAY_FPS" entry END */


    display_main_start_pos = (DISPLAY_START_POS *) malloc(sizeof(DISPLAY_START_POS) * 1);
    void DISPLAY_START_POSITION_default(void)
    {
        cfg_value = (char *) al_get_config_value(default_cfg, "DISPLAY_START_POSITION", "adapter");
        display_main_start_pos->adapter = atoi(cfg_value);
        cfg_value = (char *) al_get_config_value(default_cfg, "DISPLAY_START_POSITION", "x");
        display_main_start_pos->x = atoi(cfg_value);
        cfg_value = (char *) al_get_config_value(default_cfg, "DISPLAY_START_POSITION", "y");
        display_main_start_pos->y = atoi(cfg_value);
    }
    if(cfg_switch)
    {
        cfg_value = (char *) al_get_config_value(user_cfg, "DISPLAY_START_POSITION", "adapter");
    }
    if(!cfg_switch || (cfg_value ? (!strlen(cfg_value)) : 1))
    {
        cfg_value = (char *) al_get_config_value(default_cfg, "DISPLAY_START_POSITION", "adapter");
    }
    int32_var = atoi(cfg_value);
    if(int32_var >= -2)
    {
        if(int32_var >= -1){
            display_main_start_pos->adapter = int32_var;
        } else {
            display_main_start_pos->adapter = int32_var;

            if(cfg_switch)
            {
                cfg_value = (char *) al_get_config_value(user_cfg, "DISPLAY_START_POSITION", "x");
                cfg_value2 = (char *) al_get_config_value(user_cfg, "DISPLAY_START_POSITION", "y");
            } else cfg_value = cfg_value2 = NULL;

            if((cfg_value ? strlen(cfg_value) : 0)  &&  (cfg_value2 ? strlen(cfg_value2) : 0)){
                display_main_start_pos->x = atoi(cfg_value);
                display_main_start_pos->y = atoi(cfg_value2);
            } else DISPLAY_START_POSITION_default();
        }
    } else DISPLAY_START_POSITION_default();
    /* "DISPLAY_START_POSITION" section END */


    /* Free default cfg structure */
    al_destroy_config(default_cfg);

    /* Free user cfg */
    if(cfg_switch) al_destroy_config(user_cfg);
} /* application_config */

private void generate_default_cfg(ALLEGRO_CONFIG *default_cfg)
{
    /* CFG header */
    al_add_config_comment(default_cfg, NULL, ABOUT_APP_NAME " " ABOUT_ORG_NAME
                                       " v." ABOUT_APP_VERSION " " ABOUT_APP_AUTHOR);
    al_add_config_comment(default_cfg, NULL, "");

    /* Global section */
    al_add_config_comment(default_cfg, NULL, "Skip confirmation of program closure.");
    al_set_config_value(default_cfg, NULL, "SKIP_CONFIRM_EXIT", FALSE_S);

    al_add_config_comment(default_cfg, NULL, "Skip the welcome screen.");
    al_set_config_value(default_cfg, NULL, "SKIP_WELCOME_SCREEN", FALSE_S);

    al_add_config_comment(default_cfg, NULL, "Set display Frame Per Second. min: 1, max: 60");
    al_set_config_value(default_cfg, NULL, "DISPLAY_FPS", "45");

    /* DISPLAY_START_POSITION section */
    al_add_config_comment(default_cfg, "DISPLAY_START_POSITION", "Monitor is connected to graphic adapter.");
    al_add_config_comment(default_cfg, "DISPLAY_START_POSITION", "adapter: -2 -> manual: x, y");
    al_add_config_comment(default_cfg, "DISPLAY_START_POSITION", "adapter: -1 -> auto detect adapter");
    al_add_config_comment(default_cfg, "DISPLAY_START_POSITION", "adapter: >= 0 -> set manually adapter");
    al_set_config_value(default_cfg, "DISPLAY_START_POSITION", "adapter", "-1");
    al_set_config_value(default_cfg, "DISPLAY_START_POSITION", "x", "150");
    al_set_config_value(default_cfg, "DISPLAY_START_POSITION", "y", "150");
} /* generate_default_cfg */
