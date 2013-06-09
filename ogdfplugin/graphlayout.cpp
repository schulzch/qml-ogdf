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
#include "ogdf/energybased/TutteLayout.h"
#include "ogdf/energybased/DavidsonHarelLayout.h"
#include "ogdf/energybased/FMMMLayout.h"
#include "ogdf/energybased/FastMultipoleEmbedder.h"
#include "ogdf/energybased/GEMLayout.h"
#include "ogdf/energybased/MultilevelLayout.h"
#include "ogdf/energybased/SpringEmbedderFR.h"
#include "ogdf/energybased/SpringEmbedderFRExact.h"
#include "ogdf/energybased/SpringEmbedderKK.h"
#include "ogdf/energybased/StressMinimization.h"
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
#include <QQmlInfo>

#define CREATE_MODULE(name) case name: \
    layout = new ogdf::name(); \
    break

GraphLayout::GraphLayout(ogdf::GraphAttributes &attributes, QObject *parent)
    : QObject(parent), m_attributes(&attributes),
      m_layout(new ogdf::FMMMLayout()), m_algorithm(GraphLayout::FMMMLayout),
      m_valid(false)
{
}

GraphLayout::Algorithm GraphLayout::algorithm() const
{
    return m_algorithm;
}

void GraphLayout::setAlgorithm(Algorithm algorithm)
{
    if (algorithm == m_algorithm) {
        return;
    }
    // Create layout module by name.
    ogdf::LayoutModule *layout = 0;
    switch (algorithm) {
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
    CREATE_MODULE(StressMinimization);
    CREATE_MODULE(SugiyamaLayout);
    CREATE_MODULE(TreeLayout);
    CREATE_MODULE(TutteLayout);
    CREATE_MODULE(UpwardPlanarizationLayout);
    CREATE_MODULE(VisibilityLayout);
    }
    if (layout) {
        m_layout.reset(layout);
        m_algorithm = algorithm;
        invalidate();
        emit algorithmChanged();
    }
}

bool GraphLayout::valid() const
{
    return m_valid;
}

void GraphLayout::call()
{
    if (m_valid) {
        return;
    }
    try {
        m_layout->call(*m_attributes);
        m_valid = true;
        emit validChanged();
    } catch (ogdf::AlgorithmFailureException &e) {
        QString reason = QString("of an unknown reason (%1)").arg(e.exceptionCode());
        switch (e.exceptionCode()) {
        case ogdf::afcUnknown:
            // Do nothing.
            break;
        case ogdf::afcIllegalParameter:
            reason = "of an illegal parameter";
            break;
        case ogdf::afcNoFlow:
            reason = "min-cost flow solver could not find a legal flow";
            break;
        case ogdf::afcSort:
            reason = "sequence is not sorted";
            break;
        case ogdf::afcLabel:
            reason = "labelling failed";
            break;
        case ogdf::afcExternalFace:
            reason = "external face is not correct";
            break;
        case ogdf::afcForbiddenCrossing:
            reason = "crossing were forbidden";
            break;
        case ogdf::afcTimelimitExceeded:
            reason = "timelimit exceeded";
            break;
        case ogdf::afcNoSolutionFound:
            reason = "it could not find a solution";
            break;
        case ogdf::afcSTOP:
            // Do nothing.
            break;
        }
        qmlInfo(this) << "Layout algorithm failed, because " << reason;
    } catch (ogdf::PreconditionViolatedException &e) {
        QString reason = QString("An unknown reason (%1)").arg(e.exceptionCode());
        switch (e.exceptionCode()) {
        case ogdf::pvcUnknown:
            // Do nothing.
            break;
        case ogdf::pvcSelfLoop:
            reason = "Graph contains a self-loop, which";
            break;
        case ogdf::pvcTreeHierarchies:
            reason = "Graph is not a tree, which";
            break;
        case ogdf::pvcAcyclicHierarchies:
            reason = "Graph is not acyclic, which";
            break;
        case ogdf::pvcSingleSource:
            reason = "Graph has not a single source, which";
            break;
        case ogdf::pvcUpwardPlanar:
            reason = "Graph is not upward planar, which";
            break;
        case ogdf::pvcTree:
            reason = "Graph is not a rooted tree, which";
            break;
        case ogdf::pvcForest:
            reason = "Graph is not a rooted forest, which";
            break;
        case ogdf::pvcOrthogonal:
            reason = "Layout is not orthogonal, which";
            break;
        case ogdf::pvcPlanar:
            reason = "Graph is not planar, which";
            break;
        case ogdf::pvcClusterPlanar:
            reason = "Graph is not cluster planar, which";
            break;
        case ogdf::pvcNoCopy:
            reason = "Graph is not a copy of the corresponding graph, which";
            break;
        case ogdf::pvcConnected:
            reason = "Graph is not connected, which";
            break;
        case ogdf::pvcBiconnected:
            reason = "Graph is not twoconnected, which";
            break;
        case ogdf::pvcSTOP:
            // Do nothing.
            break;
        }
        qmlInfo(this) << reason << " violates layout preconditions";
    } catch (ogdf::Exception &) {
        qmlInfo(this) << "OGDF exception caught";
    } catch (...) {
        qmlInfo(this) << "Unknown exception caught";
    }
}

void GraphLayout::invalidate()
{
    if (m_valid) {
        m_valid = false;
        emit validChanged();
    }
}
