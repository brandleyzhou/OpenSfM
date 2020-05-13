#include <algorithm>
#include <map/landmark.h>
#include <map/shot.h>
#include <slam/guided_matching.h>

namespace map
{
Landmark::Landmark(const LandmarkId lm_id, const Eigen::Vector3d& global_pos, const std::string& name):
  id_(lm_id), name_(name), global_pos_(global_pos), color_(255,0,0)
{

}
Eigen::Vector3f 
Landmark::GetObservationInShot(Shot* shot) const {
  const auto obs_id = observations_.at(shot);
  return shot->GetKeyPointEigen(obs_id);
}

void 
Landmark::SetReprojectionErrors(const std::unordered_map<std::string, Eigen::VectorXd> reproj_errors)
{
  reproj_errors_ = reproj_errors;
}


double 
Landmark::ComputeDistanceFromRefFrame() const
{
  const Eigen::Vector3d cam_to_lm_vec = global_pos_ - ref_shot_->GetPose().GetOrigin();
  return cam_to_lm_vec.norm();
}

// const auto& Landmark::GetObservations() const 
// {
//   for (const auto& obs : observations_)
//   {
//     std::cout << "obs: " << obs.first->name_ << ", " << obs.second << std::endl;
//   } 
//   return observations_; 
// }

}; //namespace map
