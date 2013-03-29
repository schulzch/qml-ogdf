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
#include "graphlayout.h"
#include "ogdf/basic/PreprocessorLayout.h"
#include "ogdf/energybased/CoinTutteLayout.h"
#include "ogdf/energybased/DavidsonHarelLayout.h"
#include "ogdf/energybased/FMMMLayout.h"
#include "ogdf/energybased/FastMultipoleEmbedder.h"
#include "ogdf/energybased/GEMLayout.h"
#include "ogdf/energybased/MultilevelLayout.h"
#include "ogdf/energybased/SpringEmbedderFR.h"
#include "ogdf/energybased/SpringEmbedderFRExact.h"
#include "ogdf/energybased/SpringEmbedderKK.h"
#include "ogdf/energybased/StressMajorizationSimple.h"
#include "ogdf/energybased/multilevelmixer/MMMExampleFastLayout.h"
#include "ogdf/energybased/multilevelmixer/MMMExampleNiceLayout.h"
#include "ogdf/energybased/multilevelmixer/MMMExampleNoTwistLayout.h"
#include "ogdf/energybased/multilevelmixer/MixedForceLayout.h"
#include "ogdf/energybased/multilevelmixer/ModularMultilevelMixer.h"
#include "ogdf/energybased/multilevelmixer/ScalingLayout.h"
#include "ogdf/layered/SugiyamaLayout.h"
#include "ogdf/misclayout/BalloonLayout.h"
#include "ogdf/misclayout/CircularLayout.h"
#include "ogdf/packing/ComponentSplitterLayout.h"
#include "ogdf/planarity/PlanarizationGridLayout.h"
#include "ogdf/planarity/PlanarizationLayout.h"
#include "ogdf/planarlayout/FPPLayout.h"
#include "ogdf/planarlayout/MixedModelLayout.h"
#include "ogdf/planarlayout/PlanarDrawLayout.h"
#include "ogdf/planarlayout/PlanarStraightLayout.h"
#include "ogdf/planarlayout/SchnyderLayout.h"
#include "ogdf/tree/RadialTreeLayout.h"
#include "ogdf/tree/TreeLayout.h"
#include "ogdf/upward/DominanceLayout.h"
#include "ogdf/upward/UpwardPlanarizationLayout.h"
#include "ogdf/upward/VisibilityLayout.h"

#define CREATE_MODULE(name) case name##: \
    layoutModule = new ogdf::##name(); \
    break

GraphLayout::GraphLayout(QObject *parent)
    : QObject(parent), m_layoutModule(0)
{
    setLayout(GraphLayout::FMMMLayout);
}

GraphLayout::~GraphLayout()
{
    delete m_layoutModule;
}

GraphLayout::Layout GraphLayout::layout() const
{
    return m_layout;
}

void GraphLayout::setLayout(Layout layout)
{
    if (layout == m_layout) {
        return;
    }
    // Create layout module by name.
    ogdf::LayoutModule *layoutModule = 0;
    switch (layout) {
    CREATE_MODULE(BalloonLayout);
    CREATE_MODULE(CircularLayout);
    CREATE_MODULE(ComponentSplitterLayout);
    CREATE_MODULE(DavidsonHarelLayout);
    CREATE_MODULE(DominanceLayout);
    CREATE_MODULE(FMMMLayout);
    CREATE_MODULE(FPPLayout);
    CREATE_MODULE(FastMultipoleEmbedder);
    CREATE_MODULE(FastMultipoleMultilevelEmbedder);
    CREATE_MODULE(GEMLayout);
    CREATE_MODULE(MMMExampleFastLayout);
    CREATE_MODULE(MMMExampleNiceLayout);
    CREATE_MODULE(MMMExampleNoTwistLayout);
    CREATE_MODULE(MixedForceLayout);
    CREATE_MODULE(MixedModelLayout);
    CREATE_MODULE(ModularMultilevelMixer);
    CREATE_MODULE(MultilevelLayout);
    CREATE_MODULE(PlanarDrawLayout);
    CREATE_MODULE(PlanarStraightLayout);
    CREATE_MODULE(PlanarizationGridLayout);
    CREATE_MODULE(PlanarizationLayout);
    CREATE_MODULE(PreprocessorLayout);
    CREATE_MODULE(RadialTreeLayout);
    CREATE_MODULE(ScalingLayout);
    CREATE_MODULE(SchnyderLayout);
    CREATE_MODULE(SpringEmbedderFR);
    CREATE_MODULE(SpringEmbedderFRExact);
    CREATE_MODULE(SpringEmbedderKK);
    CREATE_MODULE(StressMajorization);
    CREATE_MODULE(SugiyamaLayout);
    CREATE_MODULE(TreeLayout);
    CREATE_MODULE(TutteLayout);
    CREATE_MODULE(UpwardPlanarizationLayout);
    CREATE_MODULE(VisibilityLayout);
    }
    if (layoutModule) {
        delete m_layoutModule;
        m_layoutModule = layoutModule;
        m_layout = layout;
        emit layoutChanged();
    }
}

void GraphLayout::call(ogdf::GraphAttributes &attribtues)
{
    Q_ASSERT(m_layoutModule);
    m_layoutModule->call(attribtues);
}
