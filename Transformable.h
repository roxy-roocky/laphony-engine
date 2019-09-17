/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/** 
 * \file   Transformable.h
 * \author Nathan Baumann
 * \brief Make an object transformable with position, rotation and scale
 * \date april 11 2019, 07:07 am
 */

#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Structs.h"

namespace Laphony
{
    /**
     * \brief Make an object transformable with position, rotation and scale. Define a pivot point.
     * 
     * 
     */
    class Transformable
    {
        protected:
            Point _position;
            double _angle;
            Vector2d _scale;
            Point _pivot;
            
            
        public:
            /**
             * \brief Default constructor
             * 
             * Construct with default values. \n
             * Position = {0,0}, angle = 0, scale = {1,1}, pivot = {0,0}. \n
             * A {x < 0, y < 0} center represent default center value which is {weight/2, height/2}
             */
            Transformable();
            
            /**
             * \brief Contructs with custom values
             * @param[in] position Position of the object
             * @param[in] angle Rotation of the object in DEG
             * @param(in] scale Scale of the object
             * @param(in] center Rotation et position center of the object
             */
            Transformable(Point const& position, double angle, Vector2d const& scale, Point const& pivot);
            
            /**
             * \brief Copy constructor. Is the default copy constructor
             * @param o Transform object to copy
             */
            Transformable(Transformable const& o) = default;
            
            /**
             * \brief Assignment operator. Is the default implementation
             * @param o Transform object to take like model
             */
            Transformable& operator=(Transformable const& t) = default;
            
            /**
             * \brief Assignment and additive operator. Add positions and angles, multiply scales. Pivot not affect.
             * @param o Transform object to take for operation.
             */
            Transformable& operator+=(Transformable const& t);
            
            
            /**
             * \brief Get the current position as Point(x, y)
             * 
             * @return Point with position
             */
            virtual Point Position() const;
            virtual void Translate(Vector2d const& v);
            
            /**
             * \brief Get the current angle in DEG modulo 360 degrees
             * @return double with scale
             */
            virtual double Angle() const;
            virtual void Rotate(double const& v);
            /**
             * \brief Get the current scale as Vector2d(x, y)
             * @return Vector2d with scale
             */
            virtual Vector2d Scale() const;
            /**
             * \brief Get the current center point
             * @return Point with current pivot
             */
            virtual Point Pivot() const;
            
            /**
             * Set the current position
             * @param point New position as Point(x, y)
             */
            virtual void Position(Point const& point);
            /**
             * Set the current angle
             * @param angle New angle in DEG as double
             */
            virtual void Angle(double const& angle);
            /**
             * Set the current scale
             * @param scale New scale as Vector2d(x, y)
             */
            virtual void Scale(Vector2d const& scale);
            /**
             * Set the pivot point
             * @param pivot new pivot as Point(x, y)
             */
            virtual void Pivot(Point const& pivot);
    };
}

#endif /* TRANSFORMABLE_H */

