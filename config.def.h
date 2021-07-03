/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(MOD,KEY,TAG) \
	{ MOD,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MOD|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MOD|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MOD|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *vdwmcmd[] = { "./vdwm_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* mode definitions */
#define NMODE (2) /* number of modes */
static const Mode modes[NMODE]; // TODO is this bad?

static Key insertkeys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Escape, setmode,        {.v = &modes[0]} },
    /*
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(MODKEY,                 XK_1,                      0)
	TAGKEYS(MODKEY,                 XK_2,                      1)
	TAGKEYS(MODKEY,                 XK_3,                      2)
	TAGKEYS(MODKEY,                 XK_4,                      3)
	TAGKEYS(MODKEY,                 XK_5,                      4)
	TAGKEYS(MODKEY,                 XK_6,                      5)
	TAGKEYS(MODKEY,                 XK_7,                      6)
	TAGKEYS(MODKEY,                 XK_8,                      7)
	TAGKEYS(MODKEY,                 XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    */
};

static Key normalkeys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XK_p,      spawn,          {.v = dmenucmd } },
	{ ShiftMask,                    XK_Return, spawn,          {.v = termcmd } },
	{ ShiftMask,                    XK_semicolon, spawn,       {.v = vdwmcmd } },
	{ 0,                            XK_b,      togglebar,      {0} },
	{ 0,                            XK_j,      focusstack,     {.i = +1 } },
	{ 0,                            XK_k,      focusstack,     {.i = -1 } },
	{ ShiftMask,                    XK_i,      incnmaster,     {.i = +1 } },
	{ ShiftMask,                    XK_d,      incnmaster,     {.i = -1 } },
	{ 0,                            XK_h,      setmfact,       {.f = -0.05} },
	{ 0,                            XK_l,      setmfact,       {.f = +0.05} },
	{ 0,                            XK_Return, zoom,           {0} },
	{ 0,                            XK_Tab,    view,           {0} },
	{ ShiftMask,                    XK_c,      killclient,     {0} },
	{ 0,                            XK_i,      setmode,        {.v = &modes[1]} },
	{ 0,                            XK_t,      setlayout,      {.v = &layouts[0]} },
	{ 0,                            XK_f,      setlayout,      {.v = &layouts[1]} },
	{ 0,                            XK_m,      setlayout,      {.v = &layouts[2]} },
	{ 0,                            XK_space,  setlayout,      {0} },
	{ ShiftMask,                    XK_space,  togglefloating, {0} },
	{ 0,                            XK_0,      view,           {.ui = ~0 } },
	{ ShiftMask,                    XK_0,      tag,            {.ui = ~0 } },
	{ 0,                            XK_comma,  focusmon,       {.i = -1 } },
	{ 0,                            XK_period, focusmon,       {.i = +1 } },
	{ ShiftMask,                    XK_comma,  tagmon,         {.i = -1 } },
	{ ShiftMask,                    XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(0,                      XK_1,                      0)
	TAGKEYS(0,                      XK_2,                      1)
	TAGKEYS(0,                      XK_3,                      2)
	TAGKEYS(0,                      XK_4,                      3)
	TAGKEYS(0,                      XK_5,                      4)
	TAGKEYS(0,                      XK_6,                      5)
	TAGKEYS(0,                      XK_7,                      6)
	TAGKEYS(0,                      XK_8,                      7)
	TAGKEYS(0,                      XK_9,                      8)
	{ ShiftMask,                    XK_q,      quit,           {0} },
};

#define BINDALL(KEYS) KEYS, LENGTH(KEYS)
/* mode(s) */
static const Mode modes[NMODE] = {
	/* symbol    key bindings         allow other keys */
	{ "",        BINDALL(normalkeys),    0 }, /* first entry is default */
	{ "INS",     BINDALL(insertkeys),    1 },
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

