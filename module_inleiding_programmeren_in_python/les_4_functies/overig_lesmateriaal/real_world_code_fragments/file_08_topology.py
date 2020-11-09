# --- Heart

### -Begin atria-

patches.heart_LA_Epi = Patch (39)
patches.heart_LA_Endo = Patch (65)
patches.heart_LA_Endo_Septum = Patch (41)
patches.heart_LA_Septum_border = Patch (52)
patches.heart_LA_Epi_Endo = Patch (115)

patches.heart_RA_Epi = Patch (45)
patches.heart_RA_Endo = Patch (60)
patches.heart_RA_Endo_Septum = Patch (42)
patches.heart_RA_Septum_border = Patch (51)
patches.heart_RA_Epi_Endo = Patch (117)

patches.heart_LARA_Septum_border = Patch (12)

shells.heart_LA_wall = Shell (patches.heart_LA_Epi, patches.heart_LA_Endo, patches.heart_LA_Epi_Endo, -patches.heart_LA_Septum_border, patches.heart_LARA_Septum_border)
hulls.heart_LA_wall = Hull (shells.heart_LA_wall, speed = 0.85)

shells.heart_RA_wall = Shell (patches.heart_RA_Epi, patches.heart_RA_Endo, patches.heart_RA_Epi_Endo, -patches.heart_RA_Septum_border, -patches.heart_LARA_Septum_border)
hulls.heart_RA_wall = Hull (shells.heart_RA_wall, speed = 0.85)

shells.heart_A_Septum_wall = Shell (patches.heart_LA_Endo_Septum, patches.heart_LA_Septum_border, patches.heart_RA_Endo_Septum, patches.heart_RA_Septum_border)
hulls.heart_A_Septum_wall = Hull (shells.heart_A_Septum_wall, speed = 0)

### -End atria-

### -Begin origins-

### origins.name = Origin (unique vertex colour, time = tijd in seconden)
origins.sinusnode = Origin (2, time = 0)

###

### -Begin pathways-

### pathways.name = Pathway (kleur bundel, kleur ingang, kleur uitgang, speed =xx, delay =xx) deze kunnen beiden weggelaten worden, default speed = 1m/s en default delay = 0s
pathways.bachmansbundle = Pathway (3, 2, 13, delay = 0)

# AV node = vertex 8
pathways.RBB = Pathway (75, 2, 76, delay = 0.12)
pathways.LBB = Pathway (90, 2, 91, delay = 0.12)

###

### -Begin valves-

patches.heart_TricusV_RA = Patch (112)
patches.heart_TricusV_RV = Patch (113)
patches.heart_TricusV_border = Patch (114)
patches.heart_TricusV_Epi = Patch (57)
patches.heart_RV_Epi_Endo = Patch (92)

patches.heart_MitralV_LA = Patch (24)
patches.heart_MitralV_LV = Patch (23)
patches.heart_MitralV_border = Patch (74)
patches.heart_MitralV_Epi = Patch (50)
patches.heart_LV_Epi_Endo = Patch (99)

patches.heart_MitralV_TricusV_border = Patch (59)

shells.heart_TricusV = Shell (patches.heart_TricusV_RA, patches.heart_TricusV_RV, patches.heart_TricusV_border)
hulls.heart_TricusV = Hull (shells.heart_TricusV, speed = 0)

shells.heart_TricusV_border = Shell (-patches.heart_RA_Epi_Endo, -patches.heart_RV_Epi_Endo, -patches.heart_TricusV_border, patches.heart_TricusV_Epi, -patches.heart_MitralV_TricusV_border)
hulls.heart_TricusV_border = Hull (shells.heart_TricusV_border, speed = 0)

shells.heart_MitralV = Shell (patches.heart_MitralV_LA, patches.heart_MitralV_LV, patches.heart_MitralV_border)
hulls.heart_MitralV = Hull (shells.heart_MitralV, speed = 0)

shells.heart_MitralV_border = Shell (-patches.heart_LA_Epi_Endo, -patches.heart_LV_Epi_Endo, -patches.heart_MitralV_border, patches.heart_MitralV_Epi, patches.heart_MitralV_TricusV_border)
hulls.heart_MitralV_border = Hull (shells.heart_MitralV_border, speed = 0)

### -End valves-

### -Begin ventricles-

patches.heart_LV_Epi = Patch (4)
patches.heart_LV_Endo = Patch (5)
patches.heart_LV_Endo_Septum = Patch (7)
patches.heart_LV_Septum_border = Patch (69)

patches.heart_RV_Epi = Patch (14)
patches.heart_RV_Endo = Patch (18)
patches.heart_RV_Endo_Septum = Patch (25)
patches.heart_RV_Septum_border = Patch (70)

patches.heart_LVRV_Septum = Patch (107)
patches.heart_LVRV_Septum_border = Patch (105)

shells.heart_LV_wall = Shell (patches.heart_LV_Epi, patches.heart_LV_Endo, patches.heart_LV_Epi_Endo, patches.heart_LV_Septum_border, patches.heart_LVRV_Septum_border)
hulls.heart_LV_wall = Hull (shells.heart_LV_wall, speed = 0.7)

shells.heart_RV_wall = Shell (patches.heart_RV_Epi, patches.heart_RV_Endo, patches.heart_RV_Epi_Endo, patches.heart_RV_Septum_border, -patches.heart_LVRV_Septum_border)
hulls.heart_RV_wall = Hull (shells.heart_RV_wall, speed = 0.7)

shells.heart_LV_Septum_wall = Shell (-patches.heart_LV_Endo_Septum, -patches.heart_LV_Septum_border, patches.heart_LVRV_Septum)
hulls.heart_LV_Septum_wall = Hull (shells.heart_LV_Septum_wall, speed = 0.7)

shells.heart_RV_Septum_wall = Shell (-patches.heart_RV_Endo_Septum, -patches.heart_RV_Septum_border, -patches.heart_LVRV_Septum)
hulls.heart_RV_Septum_wall = Hull (shells.heart_RV_Septum_wall, speed = 0.7)

### -End ventricles-

# --- Epicardial source model

patches.heart_AortaV = Patch (53)

shells.heart_Epicard = Shell (patches.heart_LA_Epi, patches.heart_RA_Epi, patches.heart_LV_Epi, patches.heart_RV_Epi, patches.heart_AortaV, patches.heart_MitralV_Epi, patches.heart_TricusV_Epi)

# Source patch.
# Don't include patches.heart_AortaV, this patch does not bound a hull with a well defined propagation speed.
# So it cannot be a source during a simulation.

shells.source = Shell (patches.heart_LA_Epi, patches.heart_RA_Epi, patches.heart_LV_Epi, patches.heart_RV_Epi, patches.heart_MitralV_Epi, patches.heart_TricusV_Epi)

# --- Lungs

patches.lung_L = Patch (30)
shells.lung_L = Shell (patches.lung_L)
hulls.lung_L = Hull (shells.lung_L, sigma = 0.038)

patches.lung_R = Patch (35)
shells.lung_R = Shell (patches.lung_R)
hulls.lung_R = Hull (shells.lung_R, sigma = 0.038)

# --- Other organs

patches.liver = Patch (49)
shells.liver = Shell (patches.liver)
hulls.liver = Hull (shells.liver, sigma = 0.027)

patches.spleen = Patch (119)
shells.spleen = Shell (patches.spleen)
hulls.spleen = Hull (shells.spleen, sigma = 0.039)

# --- Whole thorax

patches.thorax = Patch (103)
shells.thorax = Shell (patches.thorax)
hulls.thorax = Hull (shells.thorax, shells.heart_Epicard, shells.lung_L, shells.lung_R, shells.liver, shells.spleen, sigma = 0.201)

