/* Copyright (c) 2012 Stanislaw Halik
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */
#include "ftnoir_filter_accela/ftnoir_filter_accela.h"
#include "math.h"
#include <QDebug>
#include <float.h>
#include "facetracknoir/global-settings.h"

FTNoIR_Filter::FTNoIR_Filter()
{
	first_run = true;
	loadSettings();
}

FTNoIR_Filter::~FTNoIR_Filter()
{

}

void FTNoIR_Filter::loadSettings() {
	QSettings settings("opentrack");	// Registry settings (in HK_USER)

	QString currentFile = settings.value ( "SettingsFile", QCoreApplication::applicationDirPath() + "/Settings/default.ini" ).toString();
	QSettings iniFile( currentFile, QSettings::IniFormat );		// Application settings (in INI-file)

	iniFile.beginGroup ( "Accela" );
    zoom_factor = iniFile.value("zoom-slowness", 0).toDouble();
    rotation_alpha = iniFile.value("rotation-alpha", ACCELA_SMOOTHING_ROTATION).toDouble();
    translation_alpha = iniFile.value("translation-alpha", ACCELA_SMOOTHING_TRANSLATION).toDouble();
	iniFile.endGroup ();
}

static double parabola(const double a, const double x)
{
    const double a1 = 1./a;
    return a1 * x * x;
}

void FTNoIR_Filter::FilterHeadPoseData(double *current_camera_position,
                                       double *target_camera_position,
                                       double *new_camera_position,
                                       double *last_post_filter_values)
{
	if (first_run)
	{
        for (int i = 0; i < 6; i++)
        {
            new_camera_position[i] = target_camera_position[i];
            current_camera_position[i] = target_camera_position[i];
        }

		first_run = false;
		return;
	}

    for (int i=0;i<6;i++)
	{
        const double vec = target_camera_position[i] - current_camera_position[i];
		const int sign = vec < 0 ? -1 : 1;
		const double x = fabs(vec);
        const double a = i >= 3 ? rotation_alpha : translation_alpha;
        const double reduction = 1. / std::max(1., 1. + zoom_factor * -last_post_filter_values[TZ] / 1000);
        const double velocity = parabola(a, x) * reduction;
		const double result = current_camera_position[i] + velocity * sign;
        const bool done = sign > 0 ? result >= target_camera_position[i] : result <= target_camera_position[i];
        new_camera_position[i] = current_camera_position[i] = done ? target_camera_position[i] : result;
	}
}

extern "C" FTNOIR_FILTER_BASE_EXPORT IFilter* CALLING_CONVENTION GetConstructor()
{
    return new FTNoIR_Filter;
}
