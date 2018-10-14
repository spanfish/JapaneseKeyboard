//
//  DrawView.h
//  JPKB
//
//  Created by xwang on 10/3/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HandWritingController.h"
@interface DrawView : UIImageView {
    UIImage *lastDrawImage;
    UIBezierPath *bezierPath;
}
@property(nonatomic, strong) HandWritingController *controller;

-(void) clearPoints;
@end
