#include <Shinobi.h>
#include "lightvalues.h"

#define OBJECT  object_tea_Teapot1_Teapot1
extern NJS_OBJECT OBJECT[];

extern NJS_MATRIX   matrix[8];
extern NJS_VERTEX_BUF   vbuf[4096];

NJS_VIEW    view;
NJS_LIGHT   simple;
NJS_LIGHT   lighte;
NJS_LIGHT   lightd;

Sint32  xx,yy,zz = 0;
const char* modename[]={ "TWO LIGHTS", "SIMPLE", "EASY" };
Uint8 mode=0;
Uint8 selection = 0;
bool show_true_dir = false;
bool hide_text = false;

char selection_y[] = { //Y coordinates for cursor
    7, 8, 9,    //XYZ for light 1
    11, 12, 13, //RGB for light 1
    15, 16, 17, //ADS for light 1
    22, 23, 24, //XYZ for light 2
    26, 27, 28, //RGB for light 2
    30, 31, 32  //ADS for light 2
};

void UpdateLighting()
{
    //Clean up all lights
    njDeleteLight(&lighte);
    njDeleteLight(&lightd);
    njDeleteLight(&simple);
    //Two lights mode
    if (mode == 0)
    {
        //ENV light
        njCreateLight(&lighte, 0x13);
        njSetLightColor(&lighte, lighte_r, lighte_g, lighte_b);
        njSetLightIntensity(&lighte, lighte_s, lighte_d, lighte_a);
        njSetLightDirection(&lighte, lighte_x, lighte_y, lighte_z);
        //DIR light
        njCreateLight(&lightd, 0x13);
        njSetLightColor(&lightd, lightd_r, lightd_g, lightd_b);
        njSetLightIntensity(&lightd, lightd_s, lightd_d, lightd_a);
        njSetLightDirection(&lightd, lightd_x, lightd_y, lightd_z);
    }
    //Simple mode
    else if (mode == 1)
    {
        njCreateLight(&simple, 0x13);
        njSetLightColor(&simple, simple_r, simple_g, simple_b);
        njSetLightIntensity(&simple, simple_s, simple_d, simple_a);
        njSetLightDirection(&simple, simple_x, simple_y, simple_z);
    }
}

void Input(const PDS_PERIPHERAL* pad)
{
    float valueadd = 0.0f;
    //Show or hide text
    if (pad->press & PDD_DGT_TX || pad->press & PDD_DGT_TY) hide_text = !hide_text;
    //Show njVector-ed direction
    if (pad->press & PDD_DGT_TL || pad->press & PDD_DGT_TR) show_true_dir = !show_true_dir;
    //Switch modes
    if (pad->press & PDD_DGT_ST)
    {
        mode++;
        if (mode > 2) mode = 0;
        UpdateLighting();
    }
    //Move teapot
    xx += pad->y1 * -4;
    yy += pad->x1 * 4;
    //Move cursor
    if (pad->press & PDD_DGT_KD) selection++;
    if (pad->press & PDD_DGT_KU) selection--;
    if (mode == 0)
    {
        if (selection < 0) selection = 17;
        if (selection > 17) selection = 0;
    }
    else if (mode == 1)
    {
        if (selection < 0) selection = 8;
        if (selection > 8) selection = 0;
    }
    else if (mode == 2)
    {
        if (selection < 0) selection = 7;
        if (selection > 7) selection = 0;
    }
    //Increase or decrease values
    if (pad->press & PDD_DGT_KR || pad->press & PDD_DGT_KL || pad->on & PDD_DGT_TA || pad->on & PDD_DGT_TB)
    {
        if (pad->press & PDD_DGT_KR) valueadd = 0.1f;
        else if (pad->press & PDD_DGT_KL) valueadd = -0.1f;
        else if (pad->on & PDD_DGT_TA) valueadd = 0.01f;
        else if (pad->on & PDD_DGT_TB) valueadd = -0.01f;
        if (mode == 0)
        {
            if (selection == 0)       lighte_x += valueadd;
            else if (selection == 1)  lighte_y += valueadd;
            else if (selection == 2)  lighte_z += valueadd;
            else if (selection == 3)  lighte_r += valueadd;
            else if (selection == 4)  lighte_g += valueadd;
            else if (selection == 5)  lighte_b += valueadd;
            else if (selection == 6)  lighte_a += valueadd;
            else if (selection == 7)  lighte_d += valueadd;
            else if (selection == 8)  lighte_s += valueadd;
            else if (selection == 9)  lightd_x += valueadd;
            else if (selection == 10) lightd_y += valueadd;
            else if (selection == 11) lightd_z += valueadd;
            else if (selection == 12) lightd_r += valueadd;
            else if (selection == 13) lightd_g += valueadd;
            else if (selection == 14) lightd_b += valueadd;
            else if (selection == 15) lightd_a += valueadd;
            else if (selection == 16) lightd_d += valueadd;
            else if (selection == 17) lightd_s += valueadd;
            if (lighte_r < 0) lighte_r = 1;
            if (lighte_g < 0) lighte_g = 1;
            if (lighte_b < 0) lighte_b = 1;
            if (lighte_a < 0) lighte_a = 1;
            if (lighte_d < 0) lighte_d = 1;
            if (lighte_s < 0) lighte_s = 1;
            if (lightd_r < 0) lightd_r = 1;
            if (lightd_g < 0) lightd_g = 1;
            if (lightd_b < 0) lightd_b = 1;
            if (lightd_a < 0) lightd_a = 1;
            if (lightd_d < 0) lightd_d = 1;
            if (lightd_s < 0) lightd_s = 1;
        }
        else if (mode == 1)
        {
            if      (selection == 0)  simple_x += valueadd;
            else if (selection == 1)  simple_y += valueadd;
            else if (selection == 2)  simple_z += valueadd;
            else if (selection == 3)  simple_r += valueadd;
            else if (selection == 4)  simple_g += valueadd;
            else if (selection == 5)  simple_b += valueadd;
            else if (selection == 6)  simple_a += valueadd;
            else if (selection == 7)  simple_d += valueadd;
            else if (selection == 8)  simple_s += valueadd;
            if (simple_r < 0) simple_r = 1;
            if (simple_g < 0) simple_g = 1;
            if (simple_b < 0) simple_b = 1;
            if (simple_a < 0) simple_a = 1;
            if (simple_d < 0) simple_d = 1;
            if (simple_s < 0) simple_s = 1;
        }
        else if (mode == 2)
        {
            if (selection == 0)       easy_x += valueadd;
            else if (selection == 1)  easy_y += valueadd;
            else if (selection == 2)  easy_z += valueadd;
            else if (selection == 3)  easy_r += valueadd;
            else if (selection == 4)  easy_g += valueadd;
            else if (selection == 5)  easy_b += valueadd;
            else if (selection == 6)  easy_a += valueadd;
            else if (selection == 7)  easy_d += valueadd;
            if (easy_r < 0) easy_r = 1;
            if (easy_g < 0) easy_g = 1;
            if (easy_b < 0) easy_b = 1;
            if (easy_a < 0) easy_a = 1;
            if (easy_d < 0) easy_d = 1;
        }
        valueadd = 0;
    }
}

void Vblank()
{
    if (!hide_text)
    {
        njPrintColor(0xCC30F030);
        njPrint(NJM_LOCATION(0, selection_y[selection]), ">");
        njPrintColor(0xCCC0C0C0);
        njPrint(NJM_LOCATION(14, 1), "-- NINJA LIGHT TEST --");
        njPrint(NJM_LOCATION(1, 34), "Controls: ANALOG to rotate model,");
        njPrint(NJM_LOCATION(1, 35), "TRIGGERS to show unit direction,");
        njPrint(NJM_LOCATION(1, 36), "START to change mode, UP / DOWN to move cursor,");
        njPrint(NJM_LOCATION(1, 37), "A / B / LEFT / RIGHT to change values");
        njPrint(NJM_LOCATION(1, 38), "X / Y to hide all text");
        njPrint(NJM_LOCATION(1, 3), "MODE: %s", modename[mode]);
        //Two lights mode
        if (mode == 0)
        {
            //ENV light
            njPrintC(NJM_LOCATION(1, 5), "LIGHT 1");
            if (!show_true_dir)
            {
                njPrint(NJM_LOCATION(1, 7), "X  : %f", lighte_x);
                njPrint(NJM_LOCATION(1, 8), "Y  : %f", lighte_y);
                njPrint(NJM_LOCATION(1, 9), "Z  : %f", lighte_z);
            }
            else
            {
                njPrint(NJM_LOCATION(1, 7), "X  : %f", lighte.vctr.x);
                njPrint(NJM_LOCATION(1, 8), "Y  : %f", lighte.vctr.y);
                njPrint(NJM_LOCATION(1, 9), "Z  : %f", lighte.vctr.z);
            }
            njPrint(NJM_LOCATION(1, 11), "R  : %f", lighte.attr.argb.r);
            njPrint(NJM_LOCATION(1, 12), "G  : %f", lighte.attr.argb.g);
            njPrint(NJM_LOCATION(1, 13), "B  : %f", lighte.attr.argb.b);
            njPrint(NJM_LOCATION(1, 15), "AMB: %f", lighte.attr.iamb);
            njPrint(NJM_LOCATION(1, 16), "DIF: %f", lighte.attr.idif);
            njPrint(NJM_LOCATION(1, 17), "SPC: %f", lighte.attr.ispc);
            //DIR light
            njPrintC(NJM_LOCATION(1, 20), "LIGHT 2");
            if (!show_true_dir)
            {
                njPrint(NJM_LOCATION(1, 22), "X  : %f", lightd_x);
                njPrint(NJM_LOCATION(1, 23), "Y  : %f", lightd_y);
                njPrint(NJM_LOCATION(1, 24), "Z  : %f", lightd_z);
            }
            else
            {
                njPrint(NJM_LOCATION(1, 22), "X  : %f", lightd.vctr.x);
                njPrint(NJM_LOCATION(1, 23), "Y  : %f", lightd.vctr.y);
                njPrint(NJM_LOCATION(1, 24), "Z  : %f", lightd.vctr.z);
            }
            njPrint(NJM_LOCATION(1, 26), "R  : %f", lightd.attr.argb.r);
            njPrint(NJM_LOCATION(1, 27), "G  : %f", lightd.attr.argb.g);
            njPrint(NJM_LOCATION(1, 28), "B  : %f", lightd.attr.argb.b);
            njPrint(NJM_LOCATION(1, 30), "AMB: %f", lightd.attr.iamb);
            njPrint(NJM_LOCATION(1, 31), "DIF: %f", lightd.attr.idif);
            njPrint(NJM_LOCATION(1, 32), "SPC: %f", lightd.attr.ispc);
        }
        //Simple mode
        else if (mode == 1)
        {
            njPrintC(NJM_LOCATION(1, 5), "SIMPLE LIGHT");
            njPrint(NJM_LOCATION(1, 7), "X  : %f", simple_x);
            njPrint(NJM_LOCATION(1, 8), "Y  : %f", simple_y);
            njPrint(NJM_LOCATION(1, 9), "Z  : %f", simple_z);
            njPrint(NJM_LOCATION(1, 11), "R  : %f", simple.attr.argb.r);
            njPrint(NJM_LOCATION(1, 12), "G  : %f", simple.attr.argb.g);
            njPrint(NJM_LOCATION(1, 13), "B  : %f", simple.attr.argb.b);
            njPrint(NJM_LOCATION(1, 15), "AMB: %f", simple.attr.iamb);
            njPrint(NJM_LOCATION(1, 16), "DIF: %f", simple.attr.idif);
            njPrint(NJM_LOCATION(1, 17), "SPC: %f", simple.attr.ispc);
        }
        //Easy mode
        else if (mode == 2)
        {
            njPrintC(NJM_LOCATION(1, 5), "EASY LIGHT");
            njPrint(NJM_LOCATION(1, 7), "X  : %f", easy_x);
            njPrint(NJM_LOCATION(1, 8), "Y  : %f", easy_y);
            njPrint(NJM_LOCATION(1, 9), "Z  : %f", easy_z);
            njPrint(NJM_LOCATION(1, 11), "R  : %f", easy_r);
            njPrint(NJM_LOCATION(1, 12), "G  : %f", easy_g);
            njPrint(NJM_LOCATION(1, 13), "B  : %f", easy_b);
            njPrint(NJM_LOCATION(1, 15), "AMB: %f", easy_a);
            njPrint(NJM_LOCATION(1, 16), "DIF: %f", easy_d);
        }
    }
}

void njUserInit(void)
{
    njSetBorderColor(0);
    sbInitSystem(NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB555, 1);
    njInitVertexBuffer(800000, 0, 200000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njInitMatrix(matrix, 8, 0);
    njInit3D(vbuf, 4096);
    njInitView(&view);
    njSetView(&view);
    UpdateLighting();
    nwInitSystem(10, NJD_PORT_A0);
    njControl3D(NJD_CONTROL_3D_CONSTANT_ATTR);
    njSetConstantAttr(0xffffffff, NJD_FILTER_BILINEAR);
    njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
    njSetVSyncFunction(Vblank);
    njPrintSize(12);
}

Sint32 njUserMain(void)
{
    const PDS_PERIPHERAL* pad;
    pad = pdGetPeripheral(PDD_PORT_A0);
    njClearMatrix();
    njTranslate(NULL, 0.f, 0.f, -12.f);
    njRotateXYZ(NULL, xx, yy, zz);
    Input(pad);
    if (mode == 0)
    {
        //ENV light
        njSetLightColor(&lighte, lighte_r, lighte_g, lighte_b);
        njSetLightIntensity(&lighte, lighte_s, lighte_d, lighte_a);
        njSetLightDirection(&lighte, lighte_x, lighte_y, lighte_z);
        //DIR light
        njSetLightColor(&lightd, lightd_r, lightd_g, lightd_b);
        njSetLightIntensity(&lightd, lightd_s, lightd_d, lightd_a);
        njSetLightDirection(&lightd, lightd_x, lightd_y, lightd_z);
    }
    else if (mode == 1)
    {
        //Simple light
        njSetLightColor(&simple, simple_r, simple_g, simple_b);
        njSetLightIntensity(&simple, simple_s, simple_d, simple_a);
        njSetLightDirection(&simple, simple_x, simple_y, simple_z);
    }
    if (mode != 2) njDrawObject(OBJECT);
    else
    {
        njSetEasyLight(easy_x, easy_y, easy_z);
        njSetEasyLightColor(easy_r, easy_g, easy_b);
        njSetEasyLightIntensity(easy_d, easy_a);
        njEasyDrawObject(OBJECT);
    }
}

void njUserExit(void)
{
    nwExitSystem();
    njExitPrint();
    njExitTexture();
    sbExitSystem();
}