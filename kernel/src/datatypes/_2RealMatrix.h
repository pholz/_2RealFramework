/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH

		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#pragma once

#define EIGEN_DONT_ALIGN_STATICALLY
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

#include "Eigen/Dense"
//#include "Eigen/StdVector"
//#include <list>

namespace _2Real
{
#ifdef _2REAL_BLAS_DOUBLE_PRECISION
	typedef Eigen::Matrix2d		Mat2;
	typedef Eigen::Matrix3d		Mat3;
	typedef Eigen::Matrix4d		Mat4;
#else
	typedef Eigen::Matrix2f		Mat2;
	typedef Eigen::Matrix3f		Mat3;
	typedef Eigen::Matrix4f		Mat4;
#endif
	//typedef std::vector< _2Real::Mat3, Eigen::aligned_allocator< _2Real::Mat3 > >	Mat3Vector;
	//typedef std::list< _2Real::Mat3, Eigen::aligned_allocator< _2Real::Mat3 > >		Mat3List;
	//typedef std::vector< _2Real::Mat4, Eigen::aligned_allocator< _2Real::Mat4 > >	Mat4Vector;
	//typedef std::list< _2Real::Mat4, Eigen::aligned_allocator< _2Real::Mat4 > >		Mat4List;
}
