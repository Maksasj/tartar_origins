# Player

```
Set: [Pouch]
    Tag: [Item]
    Set: [Slime Juice]
        Tag: [Resource]
        Tag: [Item]
        Value: [Count] [1]
        Set: [Material]
            Tag: [Slime]
            Tag: [Slime Ball]
            Tag: [Slime Juice]
        
Set: [Wooden Sword]
    Tag: [Weapon]
    Tag: [Short Sword]
    Tag: [Item]
    Effect: [Cutting Blow]
    Set: [Stats]
        Value: [Stamina]    [3]
        Value: [Strength]   [3]
        Value: [Intellect]  [1]
        Value: [Armor]      [2]

Set: [Player]
    Effect: [_Self]
    
    Set: [Type]
        Set: [Warrior]
            Value: [Stamina]    [3]
            Value: [Strength]   [3]
            Value: [Intellect]  [1]
            Value: [Armor]      [2]
        Tag: [Humanoid]
        Tag: [Human]
        
    Set: [Metrics]
        Set: [Position]
            Value: [xCoordinate] [0]
            Value: [yCoordinate] [0]
    
    Effect: [Vision]
    Effect: [Movement]
    Effect: [Godly hand]
    
    Value: [Health] [10]
        
    Set: [Equipment]
        
```