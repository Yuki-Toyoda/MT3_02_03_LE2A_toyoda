#include <Novice.h>
#include <imgui.h>
#include "MyConst.h"
#include "MyDebug.h"
#include "MyCollision.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 回転角
	Vector3 rotate{};
	// 座標
	Vector3 translate{};

	// 平面
	Plane plane{ {0.0f, 1.0f, 0.0f}, 1.0f };

	// 線分
	Segment segment{ {-0.45, 0.35, 0.0f}, {0.0f, 0.5f, 0.0f} };
	// 色
	int32_t segmentColor = WHITE;

	// カメラ座標
	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	// カメラ回転角
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// スクリーン座標系に変換
		
		// ワールド行列生成
		Matrix4x4 worldMatrix = MyMath::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);

		// カメラ用行列生成
		Matrix4x4 cameraMatrix = MyMath::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);

		// ビュー行列生成
		Matrix4x4 viewMatrix = MyMath::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MyMath::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = MyMath::Multiply(worldMatrix, MyMath::Multiply(viewMatrix, projectionMatrix));

		// ビューポート行列生成
		Matrix4x4 viewPortmatrix = MyMath::MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		// 開始地点
		Vector3 start = MyMath::Transform(MyMath::Transform(segment.origin, worldViewProjectionMatrix), viewPortmatrix);
		// 終端地点
		Vector3 end = MyMath::Transform(MyMath::Transform(MyMath::Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewPortmatrix);

		// 衝突判定検証
		if (MyCollision::IsCollisionLine(segment, plane)) {
			segmentColor = RED;
		}
		else {
			segmentColor = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッドを描画する
		MyDebug::DrawGrid(worldViewProjectionMatrix, viewPortmatrix);

		// 平面
		MyDebug::DrawPlane(plane, worldViewProjectionMatrix, viewPortmatrix, WHITE);

		// 線分描画
		Novice::DrawLine(
			int(start.x), int(start.y),
			int(end.x), int(end.y),
			segmentColor);

		///
		/// ↑描画処理ここまで
		///

		///
		/// ↓デバック処理ここから
		///

		// デバックウィンドウ表示
		ImGui::Begin("Debug");

		// カメラ座標をいじる
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		// カメラの回転角をいじる
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);

		// 平面の座標をいじる
		ImGui::DragFloat3("normal", &plane.normal.x, 0.01f);
		plane.normal = MyMath::Normalize(plane.normal);
		ImGui::DragFloat("distance", &plane.distance, 0.01f);

		// 線分の座標をいじる
		ImGui::DragFloat3("origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("diff", &segment.diff.x, 0.01f);

		ImGui::End();

		///
		/// ↑デバック処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
