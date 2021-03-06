//
//  LFXGatewayConnection.h
//  LIFX
//
//  Created by Nick Forge on 6/09/13.
//  Copyright (c) 2013 LIFX Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LFXMessage.h"
#import "LFXGatewayDescriptor.h"

@protocol LFXGatewayConnectionDelegate;


typedef enum {
	LFXGatewayConnectionStateNotConnected,
	LFXGatewayConnectionStateConnecting,
	LFXGatewayConnectionStateConnected,
} LFXGatewayConnectionState;




@interface LFXGatewayConnection : NSObject

+ (instancetype)gatewayConnectionWithGatewayDescriptor:(LFXGatewayDescriptor *)gateway delegate:(id <LFXGatewayConnectionDelegate>)delegate;

- (instancetype)initWithGatewayDescriptor:(LFXGatewayDescriptor *)gateway delegate:(id <LFXGatewayConnectionDelegate>)delegate;

@property (nonatomic, readonly) LFXGatewayDescriptor *gatewayDescriptor;

@property (nonatomic, weak) id <LFXGatewayConnectionDelegate> delegate;



// Connection State
- (void)connect;
- (void)disconnect;

@property (nonatomic) LFXGatewayConnectionState connectionState;

- (NSString *)connectionStateString;

// To be called externally (subclasses to override)
- (void)sendMessage:(LFXMessage *)message;


// For subclasses to use when queueing messages in an outbox
+ (BOOL)newMessage:(LFXMessage *)newMessage makesQueuedMessageRedundant:(LFXMessage *)queuedMessage;

@end


@protocol LFXGatewayConnectionDelegate <NSObject>

- (void)gatewayConnection:(LFXGatewayConnection *)connection didReceiveMessage:(LFXMessage *)message fromHost:(NSString *)host;
- (void)gatewayConnectionDidConnect:(LFXGatewayConnection *)connection;
- (void)gatewayConnection:(LFXGatewayConnection *)connection didDisconnectWithError:(NSError *)error;

@end
