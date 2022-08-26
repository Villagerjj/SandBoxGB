#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <gb/drawing.h>
#include <stdio.h>

#define GameHeight SCREENHEIGHT
#define GameWidth SCREENWIDTH

uint8_t DotCache = 1;
uint8_t CurX=50;
uint8_t CurY=50;
uint8_t Chunks[360];
uint8_t dots[243040];
uint8_t dotsOLD[243040];
uint8_t temp;
//uint8_t OptiHeight = 0;

uint8_t dotLUT[160] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19};


void DrawBarrier(int x1, int y1, int x2, int y2)
{
line(x1, y1, x2, y2); //solid line
line(x1, y1+1, x2, y2+1); //solid line
}

void display()
{
    // world view updater
    for (uint8_t y = CurY - 5; y < GameHeight; y++)
    {
        for (uint8_t x = 0; x < GameWidth; x++)
        {

            if (getpix(x, y) == 0 ) // air
            {
                
                temp++;
                 
                
                if(temp == 16)
                {
                Chunks[dotLUT[y] * 20 + dotLUT[x]] = 1;
                temp = 0;
                }
                
                goto SKIP1;
            }

            if (getpix(x, y) != 0) // if the dot is not 0, wakeup the chunk
            {
                
                Chunks[dotLUT[y] * 20 + dotLUT[x]] = 0;
                
            }

            if(Chunks[dotLUT[y] * 20 + dotLUT[x]] == 1)
            {
                x = (dotLUT[x] * 8) - 1;
                y = (dotLUT[y] * 8) + 1;
                goto SKIP1;
            }

          

            if (getpix(x, y) == 3) // solid matter
            {
                goto SKIP1;
            }
            if(y == GameHeight)
            {
              goto SKIP2;
            }
            
            if (getpix(x, y) == 2 && getpix(x, y+1) != 0 && getpix(x+1, y+1) != 0 && getpix(x-1, y+1) != 0)
            {
            goto SKIP2;
            }


            if (getpix(x, y) == 1) // sand
            {
                if (getpix(x, y + 1) == 0)
                {
                    
                    if (getpix(x, y + 2) == 0)
                    {
                        if (getpix(x, y + 3) == 0)
                        {
                            plot(x, y + 3, 1, 0);
                            plot(x, y, 0, 0);
                    
                        }
                        else
                        {
                        plot(x, y + 2, 1, 0);
                        plot(x, y, 0, 0);
                        }
                    }
                    else
                    {
                    plot(x, y + 1, 1, 0);
                    plot(x, y, 0, 0);
                    }
                }
                else if (getpix(x - 1, y + 1) == 0)
                {
                    
                    if (getpix(x - 1, y + 2) == 0)
                    {
                        
                        if (getpix(x - 1, y + 3) == 0)
                        {
                            plot(x - 1, y + 3, 1, 0);
                            plot(x, y, 0, 0);
                    
                        }
                        else
                        {
                            plot(x - 1, y + 2, 1, 0);
                        plot(x, y, 0, 0);
                        }
                    }
                    else
                    {
                        plot(x - 1, y + 1, 1, 0);
                    plot(x, y, 0, 0);
                    }
                }
                else if (getpix(x + 1, y + 1) == 0)
                {
                    
                    if (getpix(x + 1, y + 2) == 0)
                    {
                        
                        if (getpix(x + 1, y + 3) == 0)
                        {
                            plot(x + 1, y + 3, 1, 0);
                            plot(x, y, 0, 0);
                    
                        }
                        else
                        {
                            plot(x + 1, y + 2, 1, 0);
                        plot(x, y, 0, 0);
                        }
                    }
                    else
                    {
                        plot(x + 1, y + 1, 1, 0);
                    plot(x, y, 0, 0);
                    }
                }

                if (getpix(x, y + 1) == 2)
                    {
                    plot(x, y + 1, 1, 0);
                    plot(x, y, 2, 0);
                    }
                else if (getpix(x - 1, y + 1) == 2)
                    {
                    plot(x - 1, y + 1, 1, 0);
                    plot(x, y, 2, 0);
                    }
                else if (getpix(x + 1, y + 1) == 2)
                    {
                    plot(x + 1, y + 1, 1, 0);
                    plot(x, y, 2, 0);
                    }

                
            }
            
            if (getpix(x, y) == 2) // water
            {
                if (getpix(x, y + 1) == 0)
                {
                    if (getpix(x, y + 2) == 0)
                    {
                        if (getpix(x, y + 3) == 0)
                        {
                        plot(x, y + 3, 2, 0);
                        plot(x, y, 0, 0);
                        }
                        else
                        {
                        plot(x, y + 2, 2, 0);
                        plot(x, y, 0, 0);
                        }
                    }
                    else
                    {
                    plot(x, y + 1, 2, 0);
                    plot(x, y, 0, 0);
                    }
                    
                }
                else if (getpix(x - 1, y + 1) == 0)
                {
                    if (getpix(x - 2, y + 2) == 0)
                    {
                        if (getpix(x - 2, y + 3) == 0)
                        {
                        plot(x - 2, y + 3, 2, 0);
                        plot(x, y, 0, 0);
                        }
                        else
                        {
                        plot(x - 2, y + 2, 2, 0);
                        plot(x, y, 0, 0);
                        }
                    
                    }
                    else
                    {
                    plot(x - 1, y + 1, 2, 0);
                    plot(x, y, 0, 0);
                    }
                    
                }
                else if (getpix(x + 1, y + 1) == 0)
                {
                    if (getpix(x + 2, y + 2) == 0)
                    {
                        if (getpix(x + 2, y + 3) == 0)
                        {
                        plot(x + 2, y + 3, 2, 0);
                        plot(x, y, 0, 0);
                        }
                        else
                        {
                        plot(x + 2, y + 2, 2, 0);
                        plot(x, y, 0, 0);
                        }
                 
                    }
                    else
                    {
                    plot(x + 1, y + 1, 2, 0);
                    plot(x, y, 0, 0);
                    }
                    
                }
                else if (getpix(x + 1, y) == 0)
                {
                     if (getpix(x + 2, y) == 0)
                    {
                    plot(x + 2, y, 2, 0);
                    plot(x, y, 0, 0);
                    
                    }
                    else
                    {
                    plot(x + 1, y, 2, 0);
                    plot(x, y, 0, 0);
                    }
                    
                }
                else if (getpix(x - 1, y) == 0)
                {
                    if (getpix(x - 2, y) == 0)
                    {  
                    plot(x - 2, y, 2, 0);
                    plot(x, y, 0, 0);
                    }
                    else
                    {
                    plot(x - 1, y, 2, 0);
                    plot(x, y, 0, 0);
                    }
                    
                }
                 goto SKIP1;
            }

        SKIP2:
        if (getpix(x, y) == 2) // stationary water
            {
                
                if (getpix(x + 1, y) == 0)
                {
                    plot(x + 1, y, 2, 0);
                    plot(x, y, 0, 0);
                }
                else if (getpix(x - 1, y) == 0)
                {
                    plot(x - 1, y, 2, 0);
                    plot(x, y, 0, 0);
                }

                SKIP1:
            }
            
        
        }
    }
}


void main(void)
{
    cpu_fast();
   // DrawBarrier(30, 100, 50, 100);
    for(uint8_t i = 0; i < 160; i++)
    {
     Chunks[i] = 1;
    }
    SHOW_BKG;
    SHOW_SPRITES;
    while (1)
    {
        uint8_t cur = joypad();

        if (cur & J_A)
        { 
            color(DotCache, DotCache, 0);
            circle(CurX, CurY, 3, 1);
            //plot(CurX, CurY, DotCache, 0);
            //plot(CurX, CurY+1, DotCache, 0);
            //plot(CurX+1, CurY, DotCache, 0);
            //plot(CurX+1, CurY+1, DotCache, 0);
           
        }

        if (cur & J_B)
        {
        }

        if (cur & J_SELECT)
        {
            if(DotCache != 3)
            {
                DotCache++;
            }
            else
            {
                DotCache = 0;
            }
        }

        if (cur & J_START)
        {
        }

        if (cur & J_UP)
        {
            CurY--;
        }
        else if (cur & J_DOWN)
        {
            CurY++;
        }

        if (cur & J_LEFT)
        {
            CurX--;
        }
        else if (cur & J_RIGHT)
        {
            CurX++;
        }

    
        display();
    }
}
