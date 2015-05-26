#ifndef BOOST_GEOMETRY_PROJECTIONS_BACON_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BACON_HPP

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

namespace boost { namespace geometry { namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace bacon
    {

            static const double HLFPI2 = 2.46740110027233965467;
            static const double EPS = 1e-10;

            struct par_bacon
            {
                int bacn;
                int ortl;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_bacon_spheroid : public base_t_f<base_bacon_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_bacon m_proj_parm;

                inline base_bacon_spheroid(const Parameters& par)
                    : base_t_f<base_bacon_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double ax, f;

                    xy_y = this->m_proj_parm.bacn ? HALFPI * sin(lp_lat) : lp_lat;
                    if ((ax = fabs(lp_lon)) >= EPS) {
                        if (this->m_proj_parm.ortl && ax >= HALFPI)
                            xy_x = sqrt(HLFPI2 - lp_lat * lp_lat + EPS) + ax - HALFPI;
                        else {
                            f = 0.5 * (HLFPI2 / ax + ax);
                            xy_x = ax - f + sqrt(f * f - xy_y * xy_y);
                        }
                        if (lp_lon < 0.) xy_x = - xy_x;
                    } else
                        xy_x = 0.;
                }
            };

            // Apian Globular I
            template <typename Parameters>
            void setup_apian(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = proj_parm.ortl = 0;
                par.es = 0.;
            }

            // Ortelius Oval
            template <typename Parameters>
            void setup_ortel(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = 0;
                proj_parm.ortl = 1;
                par.es = 0.;
            }

            // Bacon Globular
            template <typename Parameters>
            void setup_bacon(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = 1;
                proj_parm.ortl = 0;
                par.es = 0.;
            }

        }} // namespace detail::bacon
    #endif // doxygen

    /*!
        \brief Apian Globular I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_apian.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct apian_spheroid : public detail::bacon::base_bacon_spheroid<Geographic, Cartesian, Parameters>
    {
        inline apian_spheroid(const Parameters& par) : detail::bacon::base_bacon_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::bacon::setup_apian(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Ortelius Oval projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_ortel.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct ortel_spheroid : public detail::bacon::base_bacon_spheroid<Geographic, Cartesian, Parameters>
    {
        inline ortel_spheroid(const Parameters& par) : detail::bacon::base_bacon_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::bacon::setup_ortel(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Bacon Globular projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_bacon.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct bacon_spheroid : public detail::bacon::base_bacon_spheroid<Geographic, Cartesian, Parameters>
    {
        inline bacon_spheroid(const Parameters& par) : detail::bacon::base_bacon_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::bacon::setup_bacon(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class apian_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<apian_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class ortel_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<ortel_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class bacon_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<bacon_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void bacon_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("apian", new apian_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("ortel", new ortel_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("bacon", new bacon_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_BACON_HPP

