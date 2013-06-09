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
 * This class provides graph layout.
 */
class GraphLayout : public QObject
{
    Q_OBJECT
    Q_ENUMS(Algorithm)
    Q_PROPERTY(Algorithm algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
public:
    enum Algorithm {
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
        StressMinimization,
        SugiyamaLayout,
        TreeLayout,
        TutteLayout,
        UpwardPlanarizationLayout,
        VisibilityLayout
    };

    GraphLayout(ogdf::GraphAttributes &attributes, QObject *parent = 0);

    Algorithm algorithm() const;
    void setAlgorithm(Algorithm algorithm);

    bool valid() const;

    Q_INVOKABLE void call();

signals:
    void algorithmChanged();
    void validChanged();

public slots:
    void invalidate();

private:
    Q_DISABLE_COPY(GraphLayout)

    QScopedPointer<ogdf::LayoutModule> m_layout;
    ogdf::GraphAttributes *m_attributes;
    Algorithm m_algorithm;
    bool m_valid;
};

#endif
