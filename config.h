/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;	/* 1 means swallow floating windows by default */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static const int splitstatus	    = 1;
static const char *splitdelim	    = "";
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "cozette:size=10" };
static const char dmenufont[]       = "cozette:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_gray5[]	    = "#000000";
static const char col_cyan[]        = "#005577";
static const char col_acc[]	    = "#bd93f9";
static const char col_white[]	    = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray5, col_white },
	[SchemeSel]  = { col_white, col_acc,   col_acc   },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	       /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
		{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
		{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
		{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
		{ "sdl",     NULL,     "sdl",	       0,	  1,	      0,           1,        -1 },
		{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray5, "-nf", col_white, "-sb", col_acc, "-sf", col_gray5, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key       	function        	argument */
	{ MODKEY,                       XK_p,		spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, 	spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_s,	   	spawn,	   	SHCMD("maim -su | xclip -selection clipboard -t image/png -i") },
	{ MODKEY,			XK_b,	   	spawn,	   	SHCMD("librewolf") },
	{ MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("discord") },
	{ MODKEY,			XK_n,		spawn,		SHCMD("st -e ncmpcpp") },
	{ MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD("lutris") },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("sn") },
	{ MODKEY,			XK_End,		spawn,		SHCMD("xsecurelock") },
	{ MODKEY,			XK_F5,		spawn,		SHCMD("mpc clear") },
	{ MODKEY,			XK_F6,		spawn,		SHCMD("mpc prev") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("mpc toggle") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("mpc next") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("pactl set-sink-volume 0 -5%") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("pactl set-sink-volume 0 +5%") },
	{ MODKEY|ShiftMask,		XK_F10,		spawn,		SHCMD("mpc volume -5") },
	{ MODKEY|ShiftMask,		XK_F11,		spawn,		SHCMD("mpc volume +5") },
	{ MODKEY|ShiftMask,		XK_p,		spawn,		SHCMD("bash $HOME/scripts/setlayout.sh") },
	{ MODKEY,			XK_m,		spawn,		SHCMD("bash $HOME/scripts/dmenumpd.sh") },
	{ MODKEY|ShiftMask|ControlMask, XK_b,      	togglebar,     	{0}},
	{ MODKEY,			XK_j,	   	focusstack,	{.i = +1 } },
	{ MODKEY,			XK_k,	   	focusstack,	{.i = -1 } },
	{ MODKEY,                       XK_f,      	incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      	incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      	setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      	setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      	incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      	incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      	incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      	incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      	incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      	incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      	togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      	defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_Return, 	zoom,           {0} },
	{ MODKEY,                       XK_Tab,    	view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      	killclient,     {0} },
	{ MODKEY,                       XK_t,      	setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      	setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      	setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_i,      	setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      	setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  	setlayout,      {0} },
	{ MODKEY,			XK_w,		togglefloating, {0} },
	{ MODKEY,                       XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,          	        XK_h,      	focusmon,       {.i = -1 } },
        { MODKEY,	                XK_l,      	focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask, 		XK_h,      	tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask, 		XK_l,      	tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,      	                0)
	TAGKEYS(                        XK_2,      	                1)
	TAGKEYS(                        XK_3,      	                2)
	TAGKEYS(                        XK_4,      	                3)
	TAGKEYS(                        XK_5,      	                4)
	TAGKEYS(                        XK_6,      	                5)
	TAGKEYS(                        XK_7,      	                6)
	TAGKEYS(                        XK_8,      	                7)
	TAGKEYS(                        XK_9,      	                8)
	{ MODKEY|ShiftMask,             XK_Delete, 	quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_Delete, 	quit,           {0} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

