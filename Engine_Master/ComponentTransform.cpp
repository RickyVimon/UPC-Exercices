#include "ComponentTransform.h"

#include "../GameObject.h"
#include "IMGUI/imgui.h"

void ComponentTransform::DrawView() {
	if (ImGui::TreeNode("Transform test")) {
		ImGui::Text("Position:\tX:%.f\tY:%.f\tZ:%.f ", position.x, position.y, position.z);
		ImGui::Text("Rotation:\tX:%.f\tY:%.f\tZ:%.f", rotation.x, rotation.y, rotation.z);
		ImGui::Text("Scale:\tX:%.f\tY:%.f\tZ:%.f", scaling.x, scaling.y, scaling.z);
		ImGui::TreePop();
	}
}

void ComponentTransform::CalculateWorldTransform(const float4x4& trans) {
	/*if (parent != nullptr) {
		trans = trans *
		transformation = transformation * ((Transform*) owner->parent->FindComponent(ComponentType::Transform))->transformation;
	}*/
}

void ComponentTransform::SetTransform(const aiMatrix4x4& trans) {
	localTransform.SetRow(0, float4(trans.a1, trans.a2, trans.a3, trans.a4));
	localTransform.SetRow(1, float4(trans.b1, trans.b2, trans.b3, trans.d4));
	localTransform.SetRow(2, float4(trans.c1, trans.c2, trans.c3, trans.c4));
	localTransform.SetRow(3, float4(trans.d1, trans.d2, trans.d3, trans.d4));
	/*if (owner->parent) {
		worldTransform = ((Transform*)owner->parent->FindComponent(ComponentType::Transform))->localTransform * localTransform;
	}*/
	//localTransform.Decompose(position, rotation, scale);
	worldTransform.Decompose(position, rotation, scaling);
}