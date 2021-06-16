// Template, UU version
// IGAD/NHTV/UU - Jacco Bikker - 2006-2019

#include "precomp.h"
#include "vectors.h"

namespace AdvancedGraphics {

// Math Stuff
// ----------------------------------------------------------------------------
vec3 normalize( const vec3& v ) { return v.normalized(); }
vec3 cross( const vec3& a, const vec3& b ) { return a.cross( b ); }
float dot( const vec3& a, const vec3& b ) { return a.dot( b ); }
vec3 operator * ( const float& s, const vec3& v ) { return vec3( v.x * s, v.y * s, v.z * s ); }
vec3 operator * ( const vec3& v, const float& s ) { return vec3( v.x * s, v.y * s, v.z * s ); }
vec4 operator * ( const float& s, const vec4& v ) { return vec4( v.x * s, v.y * s, v.z * s, v.w * s ); }
vec4 operator * ( const vec4& v, const float& s ) { return vec4( v.x * s, v.y * s, v.z * s, v.w * s ); }
mat4 operator * ( const mat4& a, const mat4& b )
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4) for (uint j = 0; j < 4; ++j)
		r[i + j] = (b.cell[i + 0] * a.cell[j + 0]) + (b.cell[i + 1] * a.cell[j + 4]) + (b.cell[i + 2] * a.cell[j + 8]) + (b.cell[i + 3] * a.cell[j + 12]);
	return r;
}
bool operator == ( const mat4& a, const mat4& b ) { for (uint i = 0; i < 16; i++) if (a.cell[i] != b.cell[i]) return false; return true; }
bool operator != ( const mat4& a, const mat4& b ) { return !(a == b); }
vec4 operator * ( const mat4& a, const vec4& b )
{
	return vec4( a.cell[0] * b.x + a.cell[1] * b.y + a.cell[2] * b.z + a.cell[3] * b.w,
		a.cell[4] * b.x + a.cell[5] * b.y + a.cell[6] * b.z + a.cell[7] * b.w,
		a.cell[8] * b.x + a.cell[9] * b.y + a.cell[10] * b.z + a.cell[11] * b.w,
		a.cell[12] * b.x + a.cell[13] * b.y + a.cell[14] * b.z + a.cell[15] * b.w );
}
vec4 operator * ( const vec4& b, const mat4& a )
{
	return vec4( a.cell[0] * b.x + a.cell[1] * b.y + a.cell[2] * b.z + a.cell[3] * b.w,
		a.cell[4] * b.x + a.cell[5] * b.y + a.cell[6] * b.z + a.cell[7] * b.w,
		a.cell[8] * b.x + a.cell[9] * b.y + a.cell[10] * b.z + a.cell[11] * b.w,
		a.cell[12] * b.x + a.cell[13] * b.y + a.cell[14] * b.z + a.cell[15] * b.w );
}
mat4 mat4::rotate( const vec3 l, const float a )
{
	// http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation
	mat4 M;
	const float u = l.x, v = l.y, w = l.z, ca = cosf( a ), sa = sinf( a );
	M.cell[0] = u * u + (v * v + w * w) * ca, M.cell[1] = u * v * (1 - ca) - w * sa;
	M.cell[2] = u * w * (1 - ca) + v * sa, M.cell[4] = u * v * (1 - ca) + w * sa;
	M.cell[5] = v * v + (u * u + w * w) * ca, M.cell[6] = v * w * (1 - ca) - u * sa;
	M.cell[8] = u * w * (1 - ca) - v * sa, M.cell[9] = v * w * (1 - ca) + u * sa;
	M.cell[10] = w * w  + (u * u + v * v) * ca;
	M.cell[3] = M.cell[7] = M.cell[11] = M.cell[12] = M.cell[13] = M.cell[14] = 0, M.cell[15] = 1;
	return M;
}
mat4 mat4::rotatex( const float a )
{
	mat4 M;
	const float ca = cosf( a ), sa = sinf( a );
	M.cell[5] = ca, M.cell[6] = -sa;
	M.cell[9] = sa, M.cell[10] = ca;
	return M;
}
mat4 mat4::rotatey( const float a )
{
	mat4 M;
	const float ca = cosf( a ), sa = sinf( a );
	M.cell[0] = ca, M.cell[2] = sa;
	M.cell[8] = -sa, M.cell[10] = ca;
	return M;
}
mat4 mat4::rotatez( const float a )
{
	mat4 M;
	const float ca = cosf( a ), sa = sinf( a );
	M.cell[0] = ca, M.cell[1] = -sa;
	M.cell[4] = sa, M.cell[5] = ca;
	return M;
}

vec3 operator * ( const mat4& m, const vec3& v )
{
	return vec3(
		m.cell[0] * v.x + m.cell[1] * v.y + m.cell[2] * v.z,
		m.cell[4] * v.x + m.cell[5] * v.y + m.cell[6] * v.z,
		m.cell[8] * v.x + m.cell[9] * v.y + m.cell[10] * v.z
		);
}

} // namespace AdvancedGraphics
