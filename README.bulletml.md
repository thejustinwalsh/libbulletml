BulletML reference for version  0.21.

## Table of contents

- [`<bulletml>`](#bulletml)
- [`<bullet>`](#bullet)
- [`<speed>`](#speed)
- [`<direction>`](#direction)
- [`<action>`](#action)
  - [`<fire>`](#fire)
  - [`<changeDirection>`](#changedirection)
  - [`<changeSpeed>`](#changespeed)
  - [`<accel>`](#accel)
    - [`<horizontal>`](#horizontal)
    - [`<vertical>`](#vertical)
  - [`<wait>`](#wait)
  - [`<vanish>`](#vanish)
  - [`<repeat>`](#repeat)
    - [`<times>`](#times)
- [`<term>`](#term)
- [`<bulletRef>`](#bulletref)
- [`<actionRef>`](#actionref)
- [`<fireRef>`](#fireref)
- [`<param>`](#param)
- [`STRING`](#string)
- [`NUMBER`](#number)

## `<bulletml>`

> Define the BulletML's body.

- **Attribute**: *type* (*none* &#124; *vertical* &#124; *horizontal*)
- **Content**: (*bullet* &#124; *action* &#124; *fire*)*

Define the BulletML's body.

A type attribute specifies that this barrage is for vertical scroll shooting or horizontal scroll shooting.

## `<direction>`

> Specify a direction.

- **Attribute**: *type* (*aim* | *absolute* | *relative* | *sequence*)
- **Content**: [`NUMBER`](#number)

Specify the direction in degrees.

- **aim** type means that [`NUMBER`](#number) is relative to the direction to my ship (the direction to my ship is 0, clockwise).

- **absolute** type means that [`NUMBER`](#number) is the absolute value (12 o'clock is 0, clockwise).

- **relative** type means that [`NUMBER`](#number) is relative to the direction of this bullet (0 means that the direction of this fire and the direction of the bullet are the same).

- **sequence** type means that [`NUMBER`](#number) is relative to the direction of the previous fire (0 means that the direction of this fire and the direction of the previous fire are the same).

## `<speed>`

> Specifies a speed.

- **Attribute**: *type* (*absolute* | *relative* | *sequence*)
- **Content**: [`NUMBER`](#number)

Specify the speed.

In case of the type is **relative**, if this element is included in *changeSpeed* element, the speed is relative to the current speed of this bullet. If not, the speed is relative to the speed of this bullet.

In case of the type is **sequence**, if this element is included in *changeSpeed* element, the speed is changing successively. If not, the speed is relative to the speed of the previous fire.

## `<bullet>`

> Define bullet's attributes.

- **Attribute**: *label* ([`STRING`](#string))
- **Content**: *direction?*, *speed?*, (*action* | *actionRef*)*
- **Example**:

```xml
<bullet label="downAccel">
  <direction>270</direction>
  <speed>2</speed>
  <action>
    <accel>
     <vertical>3</vertical>
     <term>120</term>
    </accel>
  </action>
</bullet>
```

Defines the direction, the speed and the action of bullet.

A label attribute labels the bullet. The labeled bullet element is referred by *bulletRef* elements.

## `<action>`

> Define bullet's action.

- **Attribute**: *label* ([`STRING`](#string))
- **Content**: (*repeat* | *fire* | *fireRef* | *changeSpeed* | *changeDirection* | *accel* | *wait* | *vanish* | *action* | *actionRef*)*
- **Example**:

```xml
<action>
  <changeSpeed>
    <speed>0</speed>
    <term>60</term>
  </changeSpeed>
  <wait>60</wait>
  <fire>
    <bullet/>
  </fire>
  <fire>
    <direction type="absolute">330 + $rand * 25</direction>
    <bulletRef label="downAccel"/>
  </fire>
  <vanish/>
</action>
```

Defines the action of bullet. The labeled action element is referred by *actionRef* elements.

### `<fire>`

> Fire a bullet.

- **Attribute**: *label* ([`STRING`](#string))
- **Content**: *direction?*, *speed?*, (*bullet* | *bulletRef*)
- **Example**:

```xml
<fire>
  <direction type="absolute">270</direction>
  <speed>2</speed>
  <bulletRef label="rocket"/>
</fire>
```

Fires a bullet to [`<direction>`](#direction) degrees at [`<speed>`](#speed). The labeled fire element is referred by [`<fireRef>`](#fireref) elements.

### `<changeDirection>`

> Change the bullet's direction.

- **Content**: *direction*, *term*

Changes the direction of bullet to [`<direction>`](#direction) degrees in [`<term>`](#term) frames. 1 frame is 1/60 seconds.

### `<changeSpeed>`

> Change the bullet's speed.

- **Content**: *speed*, *term*

Changes the speed of bullet to [`<speed>`](#speed) in [`<term>`](#term) frames.

### `<accel>`

> Accelerate a bullet.

- **Content**: *horizontal?*, *vertical?*, *term*

Accelerates a bullet [`<horizontal>`](#horizontal) in a horizontal line and [`<vertical>`](#vertical) in a vertical line in [`<term>`](#term) frames.

#### `<horizontal>`

> Specify the acceleration in a horizontal line.

- **Attribute**: *type* (*absolute* | *relative* | *sequence*)
- **Content**: [`NUMBER`](#number)

Specifies the acceleration in a horizontal line.

If the type is "relative", the acceleration is relative to the acceleration of this bullet. If the type is "sequence", the acceleration is changing successively.

#### `<vertical>`

> Specify the acceleration in a vertical line.

- **Attribute**: *type* (*absolute* | *relative* | *sequence*)
- **Content**: [`NUMBER`](#number)

Specifies the acceleration in a vertical line.

If the type is "relative", the acceleration is relative to the acceleration of this bullet. If the type is "sequence", the acceleration is changing successively.

### `<wait>`

> Wait.

- **Content**: [`NUMBER`](#number)

Waits for [`NUMBER`](#number) frames.

### `<vanish>`

> Vanish a bullet.

Vanishes a bullet.

### `<repeat>`

> Repeat an action.

- **Content**: *times*, (*action* | *actionRef*)
- **Example**:

```xml
<repeat>
  <times>100</times>
  <action>
    <fire>
      <direction type="absolute">220+$rand*100</direction>
      <bulletRef label="backBurst"/>
    </fire>
    <wait>6</wait>
  </action>
</repeat>
```

Repeats the action [`<times>`](#times) times.

#### `<times>`

> Specify the number of times.

- **Content**: [`NUMBER`](#number)

Specifies the number of times.

## `<term>`

> Specify a term.

- **Content**: [`NUMBER`](#number)

Specifies a term.

## `<bulletRef>`

> Refer to the bullet.

- **Attribute**: *label* ([`STRING`](#string))
- **Content**: *param**

Refers to the labeled bullet. This element is handled as the bullet element that has the same label.

Variables (*$1*, *$2*, *$3*, ...) in the referred element are replaced with parameters in [`<param>`](#param) (first parameter replaces *$1*, second parameter replaces *$2*, ...).

## `<actionRef>`

> Refer to the action.

- **Attribute**: *label* ([`STRING`](#string))
- **Content**: *param**

Refers to the labeled action. This element is handled as the action element that has the same label.

Variables in the referred element are replaced with parameters in [`<param>`](#param).

## `<fireRef>`

> Refer to the fire action.

- **Attribute**: *label* ([`STRING`](#string))
- **Content**: *param**

Refers to the labeled fire action. This element is handled as the fire action element that has the same label.

Variables in the referred element are replaced with parameters in [`<param>`](#param).

## `<param>`

> Specifies the parameter.

- **Contents**: [`NUMBER`](#number)

Specifies the parameter. This tag should be used when you refer to *bullet* (with [`<bulletRef>`](#bulletref)), *action* (with [`<actionRef>`](#actionref)) or *fire* (with [`<fireRef>`](#fireref)).

## STRING

> Any string

String for labels.

## NUMBER

> Expression.

- **Examples**:
  - 35
  - 360 / 16
  - 0.7 + 0.9 * $rand
  - 180 - $rank * 20
  - (2 + $1) * 0.3

Expression for specifying the number.

An addition, a subtraction, a multiplication, a division, a modulo, a bracket, and variables (*$1*, *$2*, *$3*... for parameters, *$rand* for random value (from 0 to 1), *$rank* for the rank of game difficulty (from 0 to 1)) are available.