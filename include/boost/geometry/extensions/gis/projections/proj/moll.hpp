#ifndef BOOST_GEOMETRY_PROJECTIONS_MOLL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MOLL_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 4.9.1

// Original copyright notice:
 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.


#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>
#include <boost/geometry/extensions/gis/projections/impl/aasincos.hpp>

namespace boost { namespace geometry { namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace moll
    {

            static const int MAX_ITER = 10;
            static const double LOOP_TOL = 1e-7;

            struct par_moll
            {
                double    C_x, C_y, C_p;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_moll_spheroid : public base_t_fi<base_moll_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_moll m_proj_parm;

                inline base_moll_spheroid(const Parameters& par)
                    : base_t_fi<base_moll_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double k, V;
                    int i;

                    k = this->m_proj_parm.C_p * sin(lp_lat);
                    for (i = MAX_ITER; i ; --i) {
                        lp_lat -= V = (lp_lat + sin(lp_lat) - k) /
                            (1. + cos(lp_lat));
                        if (fabs(V) < LOOP_TOL)
                            break;
                    }
                    if (!i)
                        lp_lat = (lp_lat < 0.) ? -HALFPI : HALFPI;
                    else
                        lp_lat *= 0.5;
                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(lp_lat);
                    xy_y = this->m_proj_parm.C_y * sin(lp_lat);
                }

                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    lp_lat = aasin(xy_y / this->m_proj_parm.C_y);
                    lp_lon = xy_x / (this->m_proj_parm.C_x * cos(lp_lat));
                    lp_lat += lp_lat;
                    lp_lat = aasin((lp_lat + sin(lp_lat)) / this->m_proj_parm.C_p);
                }
            };

            template <typename Parameters>
            void setup(Parameters& par, par_moll& proj_parm, double p) 
            {
                double r, sp, p2 = p + p;

                par.es = 0;
                sp = sin(p);
                r = sqrt(TWOPI * sp / (p2 + sin(p2)));
                proj_parm.C_x = 2. * r / PI;
                proj_parm.C_y = r / sp;
                proj_parm.C_p = p2 + sin(p2);
            }


            // Mollweide
            template <typename Parameters>
            void setup_moll(Parameters& par, par_moll& proj_parm)
            {
                setup(par, proj_parm, HALFPI);
            }

            // Wagner IV
            template <typename Parameters>
            void setup_wag4(Parameters& par, par_moll& proj_parm)
            {
                setup(par, proj_parm, PI/3.);
            }

            // Wagner V
            template <typename Parameters>
            void setup_wag5(Parameters& par, par_moll& proj_parm)
            {
                par.es = 0;
                proj_parm.C_x = 0.90977;
                proj_parm.C_y = 1.65014;
                proj_parm.C_p = 3.00896;
            }

        }} // namespace detail::moll
    #endif // doxygen

    /*!
        \brief Mollweide projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_moll.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct moll_spheroid : public detail::moll::base_moll_spheroid<Geographic, Cartesian, Parameters>
    {
        inline moll_spheroid(const Parameters& par) : detail::moll::base_moll_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::moll::setup_moll(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Wagner IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag4.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct wag4_spheroid : public detail::moll::base_moll_spheroid<Geographic, Cartesian, Parameters>
    {
        inline wag4_spheroid(const Parameters& par) : detail::moll::base_moll_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::moll::setup_wag4(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Wagner V projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag5.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct wag5_spheroid : public detail::moll::base_moll_spheroid<Geographic, Cartesian, Parameters>
    {
        inline wag5_spheroid(const Parameters& par) : detail::moll::base_moll_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::moll::setup_wag5(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class moll_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<moll_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class wag4_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<wag4_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class wag5_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<wag5_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void moll_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("moll", new moll_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("wag4", new wag4_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("wag5", new wag5_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_MOLL_HPP

