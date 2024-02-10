#pragma once

class Sky:
	public GameObject,
	public ObjectRenderer
{
private:
	static class Model* m_Model;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void Load();
	static void Unload();
};

