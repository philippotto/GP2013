#include "bikecontroller.h"
// OSG
#include "osg/PositionAttitudeTransform"
//troen
#include "../input/bikeinputstate.h"
#include "../view/bikeview.h"
#include "../model/bikemodel.h"
#include "../controller/fencecontroller.h"
#include "../model/physicsworld.h"
#include "../sound/audiomanager.h"

using namespace troen;

BikeController::BikeController(const std::shared_ptr<sound::AudioManager>& audioManager)
 : m_audioManager(audioManager)
{

	m_view = std::static_pointer_cast<BikeView>(std::make_shared<BikeView>());
	m_fenceController = std::make_shared<FenceController>();
	osg::ref_ptr<osg::Group> viewNode = std::static_pointer_cast<BikeView>(m_view)->getNode();
	m_model = std::static_pointer_cast<BikeModel>(std::make_shared<BikeModel>(viewNode, m_fenceController, this));
}

void BikeController::setInputState(osg::ref_ptr<input::BikeInputState>& bikeInputState)
{
	std::static_pointer_cast<BikeModel>(m_model)->setInputState(bikeInputState);
}

void BikeController::attachTrackingCamera(osg::ref_ptr<osgGA::NodeTrackerManipulator>& manipulator)
{
	osg::Matrixd cameraOffset;

	int debugNormalizer = 1;
#ifdef _DEBUG
	debugNormalizer = -1;
#endif

	cameraOffset.makeTranslate(0, debugNormalizer * 100, -20);

	osg::ref_ptr<osg::Group> viewNode = std::static_pointer_cast<BikeView>(m_view)->getNode();
	osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*> (viewNode->getChild(0));
	// set the actual node as the track node, not the pat
	manipulator->setTrackNode(pat->getChild(0));
	manipulator->setHomePosition(pat->getPosition(), pat->getPosition() * cameraOffset, osg::Vec3d(0, debugNormalizer * 1, 0));
}

void BikeController::updateModel()
{
	std::static_pointer_cast<BikeModel>(m_model)->updateState();
}

osg::ref_ptr<osg::Group> BikeController::getViewNode()
{

	osg::ref_ptr<osg::Group> group = new osg::Group();
	group->setCullingActive(false);
	group->addChild(m_fenceController->getViewNode());
	group->addChild(std::static_pointer_cast<BikeView>(m_view)->getNode());
	return group;
};

void BikeController::attachWorld(std::shared_ptr<PhysicsWorld> &world) {
	world->addRigidBodies(getRigidBodies());
	m_fenceController->attachWorld(world);
}

const std::weak_ptr<sound::AudioManager> BikeController::getAudioManager()
{
	return m_audioManager;
}
