#pragma once
// OSG
#include <osg/ref_ptr>
#include <osg/Vec3d>
#include <osg/Group>
// troen
#include "../forwarddeclarations.h"
#include "abstractmodel.h"

namespace troen
{

	class BikeModel : public AbstractModel
	{
	public:
		BikeModel(osg::ref_ptr<osg::Group> node, std::shared_ptr<FenceController> fenceController);
		void setInputState(osg::ref_ptr<input::BikeInputState> bikeInputState);
		void resetState();
		void updateState();
		void rotate(float angle);
		void accelerate(float velocity);
		float getRotation();
		float getVelocity();
		osg::Vec3d getPositionOSG();
		btVector3 BikeModel::getPositionBt();

	private:
		osg::ref_ptr<input::BikeInputState> m_bikeInputState;
		float m_velocity;
		float m_rotation;
	};
}