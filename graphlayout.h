/*
 * Copyright (c) 2013 Christoph Schulz
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details: http://www.gnu.org/copyleft/lesser
 */
#ifndef GRAPHLAYOUT_H
#define GRAPHLAYOUT_H

#include <QObject>
#include "ogdf/module/LayoutModule.h"

/**
 * @brief The GraphLayout class
 */
class GraphLayout : public QObject
{
    Q_OBJECT
    Q_ENUMS(Layout)
    Q_PROPERTY(Layout layout READ layout WRITE setLayout NOTIFY layoutChanged)
public:
    enum Layout {
        BalloonLayout,
        CircularLayout,
        ComponentSplitterLayout,
        DavidsonHarelLayout,
        DominanceLayout,
        FMMMLayout,
        FPPLayout,
        FastMultipoleEmbedder,
        FastMultipoleMultilevelEmbedder,
        GEMLayout,
        MMMExampleFastLayout,
        MMMExampleNiceLayout,
        MMMExampleNoTwistLayout,
        MixedForceLayout,
        MixedModelLayout,
        ModularMultilevelMixer,
        MultilevelLayout,
        PlanarDrawLayout,
        PlanarStraightLayout,
        PlanarizationGridLayout,
        PlanarizationLayout,
        PreprocessorLayout,
        RadialTreeLayout,
        ScalingLayout,
        SchnyderLayout,
        SpringEmbedderFR,
        SpringEmbedderFRExact,
        SpringEmbedderKK,
        StressMajorization,
        SugiyamaLayout,
        TreeLayout,
        TutteLayout,
        UpwardPlanarizationLayout,
        VisibilityLayout
    };

    GraphLayout(QObject *parent = 0);
    ~GraphLayout();

    Layout layout() const;
    void setLayout(Layout layout);

    void call(ogdf::GraphAttributes &attribtues);

signals:
    void layoutChanged();

private:
    Q_DISABLE_COPY(GraphLayout)

    ogdf::LayoutModule *m_layoutModule;
    Layout m_layout;
};

#endif
