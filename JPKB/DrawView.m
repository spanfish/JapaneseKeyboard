//
//  DrawView.m
//  JPKB
//
//  Created by xwang on 10/3/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import "DrawView.h"
#import "HandWritingController.h"

@implementation DrawView

-(id) init {
    self = [super init];
    if(self) {
        [self commonInit];
    }
    return self;
}

-(id) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self) {
        [self commonInit];
    }
    return self;
}

-(id) initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if(self) {
        [self commonInit];
    }
    return self;
}

-(void) commonInit {
    self.multipleTouchEnabled = NO;   // マルチタッチを無効化
    self.userInteractionEnabled = YES;  // タッチを検出する
    self.backgroundColor = [UIColor colorWithRed:0.886 green:1 blue:0.961 alpha:1];
}

-(void) touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesBegan:touches withEvent:event];
    if(bezierPath != nil) {
        return;  // 書いている最中に他のタッチが始まる場合は無視する
    }
    UITouch *touch = [touches anyObject];
    CGPoint currentPoint = [touch locationInView:self];
    
    [self.controller HandsInkAddStroke];
    //ストロークを追加
    [self.controller HandsInkAddPoint:currentPoint.x y:currentPoint.y];//座標をエンジンへ渡す
    bezierPath = [UIBezierPath bezierPath];
    bezierPath.lineCapStyle = kCGLineCapRound;
    bezierPath.lineWidth = 1.0;
    [bezierPath moveToPoint:currentPoint];
}

-(void) touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    if(bezierPath == nil) {
        return;  // 書いている最中に他のタッチが始まる場合は無視する
    }
    
    UITouch *touch = [touches anyObject];
    CGPoint currentPoint = [touch locationInView:self];
    
    [self.controller HandsInkAddPoint:currentPoint.x y:currentPoint.y];//座標をエンジンへ渡す
    [bezierPath addLineToPoint:currentPoint];

    [self drawLine:bezierPath];
}

-(void) touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    if (bezierPath == nil) {
        return;
    }
    UITouch* touch = [touches anyObject];
    CGPoint currentPoint = [touch locationInView:self];

    [self.controller HandsInkAddPoint:currentPoint.x y:currentPoint.y];//座標をエンジンへ渡す
    [self.controller HandsInkAddStroke];
    [bezierPath addLineToPoint:currentPoint];
    [self drawLine:bezierPath];
    bezierPath = nil;    // 他のタッチが有効になるように初期化する
    lastDrawImage = self.image;
    
    [self.controller recognize];
}
-(void) touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    //UITouch* touch = [touches anyObject];
    //_ = touch!.location(in: self)
}

-(void) drawLine:(UIBezierPath *) path {
    UIGraphicsBeginImageContext(self.frame.size);
    if (lastDrawImage != nil) {
        [lastDrawImage drawAtPoint:CGPointZero];
    }
    
    UIColor *blackColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:1];
    [blackColor setStroke];
    path.lineWidth = 5;
    
    [path stroke];
    
    self.image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
}

-(void) clearPoints {
    self.image = nil;
    lastDrawImage = nil;
    [self setNeedsDisplay];
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
