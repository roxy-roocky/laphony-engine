/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   Graphics/Animation.h
 * \author Nathan Baumann
 *
 * \date april 24 2019, 02:18 pm
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Image.h"

namespace Laphony
{
    namespace Graphics
    {
        /**
         * \brief Represent an animation from images sequence
         */
        class Animation: public virtual Displayable, public virtual Frames::Updatable, public virtual Transformable
        {
            /**
             * \brief A frame of the animation
             */
            struct Frame
            {
                /**
                 * \brief The rect from the image
                 */
                Rect rect;
                /**
                 * \brief Duration of the frame in update frames unit.
                 */
                int duration;
                /**
                 * \brief Pivot of the object for the current frame
                 */
                Point pivot;
            };
            
            public:
                /**
                 * \brief Create an animation with already created frames
                 * @param image The image containing the animation sequence
                 * @param frames The frames of the animation
                 *
                 */
                Animation(Image* image, std::vector<Frame> frames, bool autofree, bool reverseLoop = false);
                /**
                 * \brief Create an animation with rect of equal size. The image will be cut in rect from the left to the right
                 * @param image
                 * @param rect
                 * @param duration
                 * @param pivot
                 */
                Animation(Image* image, Rect const& rect, int duration, bool autofree,  Point const& pivot = {0}, bool reverseLoop = false);
                
                ~Animation();
                /**
                 * \brief Display the animation in current state 
                 * @param engine Engine where the animation must be blit. Must be the same as image
                 */
                virtual void Display(Engine* engine) override;
                /**
                 * \brief Forward the animation to one frame
                 */
                virtual void Update() override;
                
                /**
                 * Get if the animation is playing in reverse
                 * @return true if the animation is playing in reverse
                 */
                bool ReversePlay() const;
                
                /**
                 * Specify if the animation must be played is reverse
                 * @param reverse True for reverse playing
                 */
                void ReversePlay(bool reverse);
                
                /**
                 * Get the current speed of the animation
                 * @return The current speed
                 */
                double Speed() const;
                
                /**
                 * Set the speed of the animation
                 * @param speed New speed(must be greater than 0)
                 */
                void Speed(double speed);
                
                /**
                 * Reset the position of the animation to the start (or the end if reversed playing)
                 */
                void Rewind();
                
                Rect GetCurrentRect() const;
                
            private:
                
                bool Forward();
                bool Backward();
                
                std::vector<Frame> _frames;
                Image* _image;
                
                double _currentTick;
                int _currentFrame;
                
                bool _reverseLoop;
                bool _reversePlay;
                
                double _speed;
                
                bool _autofree;

        };
    }
}

#endif /* ANIMATION_H */

