/*
    GKrellM-gkfreq
    
    A plugin to GKrellM that displays the current CPU frequencies.
    
    Authors:
    Brad Davis <brad@peakunix.net> (version 1.0)
    Erik Kjellson <erikiiofph7@users.sourceforge.net>
    
    Copyright (C) 2005-2010

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
 * Using code from gkx86info http://anchois.free.fr/
 * with patches from whatdoineed2do@yahoo.co.uk
 * and knefas@gmail.com
 */

#include <gkrellm2/gkrellm.h>
#include "formatter.h"

#define CONFIG_NAME "gkfreq_cpus"
#define STYLE_NAME "gkfreq_cpus"

static GkrellmMonitor	*monitor;
static GkrellmPanel	*panel;
static GkrellmDecal	*text;
static gint	style_id;

static gint w;
static gchar  info[32];

static void
update_plugin() {
  void read_mhz() {
    char filename[64];

    char* getFilename(int i) {
      sprintf(filename, "/sys/devices/system/cpu/cpu"
              "%d"
              "/cpufreq/scaling_cur_freq", i);
      return filename;
    }

    FILE *f;
    info[0] = 0;
    int freq[8] = { 0 };

    size_t n = 0;
    for (int i = 0; i < 8; ++i) {
      f = fopen(getFilename(i), "r");

      if (f) {
        int khz;
        int assigned = fscanf(f, "%d", &khz);
        if (assigned == 1) {
          freq[i] = khz;
          n = i + 1;
        }

        fclose(f);
      }
    }

    formatFrequencies(info, 32, freq, n);
  }

  if (w == 0)
    w = gkrellm_chart_width();
	
  // dont do it too much...
  if (GK.timer_ticks % 10) return;

  read_mhz();

  text->x_off =
    (w - gdk_string_width((GdkFont*) text->text_style.font,
                          info)) / 2;
  if (text->x_off < 0)
    text->x_off = 0;

  gkrellm_draw_decal_text(panel, text, info, w);
  gkrellm_draw_panel_layers(panel);
}


static void
create_plugin(GtkWidget *vbox, gint first_create) {
  gint panel_expose_event(GtkWidget *widget, GdkEventExpose *ev) {
    gdk_draw_pixmap(widget->window,
                    widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                    panel->pixmap,
                    ev->area.x, ev->area.y,
                    ev->area.x, ev->area.y,
                    ev->area.width, ev->area.height);
    return 0;
  }

	GkrellmStyle			*style;
	GkrellmTextstyle		*ts;

	if (first_create)
		panel = gkrellm_panel_new0();

	style = gkrellm_meter_style(style_id);

	ts = gkrellm_meter_textstyle(style_id);

	text = gkrellm_create_decal_text(panel, "8MHz", ts, style,
					-1, -1, -1);

	gkrellm_panel_configure(panel, 0, style);
	gkrellm_panel_create(vbox, monitor, panel);

	if (first_create)
	    g_signal_connect(G_OBJECT (panel->drawing_area), "expose_event",
    	        G_CALLBACK (panel_expose_event), 0);
}


static GkrellmMonitor	plugin_mon = {
  CONFIG_NAME, 0,
  create_plugin, update_plugin,
  0, 0, 0, 0, 0, 0, 0, 0,
  MON_INSERT_AFTER|MON_CPU
};


GkrellmMonitor *
gkrellm_init_plugin() {
	style_id = gkrellm_add_meter_style(&plugin_mon, STYLE_NAME);
	monitor = &plugin_mon;
	return &plugin_mon;
}
