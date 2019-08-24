/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 16:29:45 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/24 14:45:07 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"


//double ft_length_vector(t_point v)
//{
//	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
////	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
//}
//
//t_point *ft_normalize_vector(t_point *v)
//{
//	double len;
//	double inv_len;
//
//	len = ft_length_vector(*v);
//	if (len > 0)
//	{
//		inv_len = 1 / len;
//		v->x *= inv_len;
//		v->y *= inv_len;
//		v->z *= inv_len;
//	}
//	return (v);
//}
//
////O = <0, 0, 0>
////for x in [-Cw/2, Cw/2] {
////		for y in [-Ch/2, Ch/2] {
////			D = CanvasToview(x, y)
////			color = TraceRay(O, D, 1, inf)
////			canvas.PutPixel(x, y, color)
////		}
////}
//
//void primary_ray()
//{
//	int x;
//	int y;
////	double PixelNDCx;
////	double PixelNDCy;
////	double PixelScreenx;
////	double PixelScreeny;
//	double ImageAspectRatio;
////	double PixelCamerax;
////	double PixelCameray;
//	t_point	dot;
//	t_point *d;
//
//	// pixel (0,0)
//	x = 0;
//	y = 0;
////	PixelNDCx = x + 0.5 / DW; /* 1600 */
////	PixelNDCy = y + 0.5 / DH; /* 855  */
////	PixelScreenx = 2 * PixelNDCx - 1;
////	PixelScreeny = 1 - 2 * PixelNDCy;
//
//
////	PixelCamerax = (2 * PixelScreenx - 1) * ImageAspectRatio * tan(60 / 2);
////	PixelCameray = (1 - 2 * PixelScreeny) * tan(60 / 2);
////
////	printf("PixelNDCx = %f, PixelNDCy = %f\n", PixelNDCx, PixelNDCy);
////	printf("PixelScreenx = %f, PixelScreeny = %f\n", PixelScreenx, PixelScreeny);
////	printf("PixelCamerax = %f, PixelCameray = %f\n", PixelCamerax, PixelCameray);
//
//
//	// PcameraSpace=(PixelCamerax,PixelCameray,−1)
//	float scale = tan (90 / 2 * M_PI / 180);
//	ImageAspectRatio = (double)DW / (double)DH;
////	float Px = (2 * ((x + 0.5) / DW) - 1) * scale * ImageAspectRatio;
////	float Py = (1 - 2 * ((y + 0.5) / DH)) * scale ;
//	float Px = (2 * (x + 0.5) / (double)DW - 1) * ImageAspectRatio * scale;
//	float Py = (1 - 2 * (y + 0.5) / (double)DH) * scale;
//	printf("scale = %f\n", scale);
//
//	dot.x = Px;
//	dot.y = Py;
//	dot.z = -1;
//
//	d = ft_normalize_vector(&dot);
//	printf("Px = %f, Py = %f\n", Px, Py);
//	printf("dot.x = %f, dot.y = %f, dot.z = %f\n", d->x, d->y, d->z);
//	// Vec3f rayOrigin (0);
//	// Vec3f rayDirection = Vec3f (Px, Py, -1) - rayOrigin; // обратите внимание, что это просто равно Vec3f (Px, Py, -1);
//	// rayDirection = normalize (rayDirection); // это направление, поэтому не забудьте нормализовать
//}

