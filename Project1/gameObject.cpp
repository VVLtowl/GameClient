#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "model.h"

#include "gameObject.h"

D3DXVECTOR3 GameObject::GetObbX()
{
    D3DXVECTOR3 vx = Right();
    D3DXVECTOR3 opt = vx * m_Scale.x*0.5f;
    return opt;
}

D3DXVECTOR3 GameObject::GetObbZ()
{
    D3DXVECTOR3 vz = Forward();
    D3DXVECTOR3 opt = vz * m_Scale.z*0.5f;
    return opt;
}
