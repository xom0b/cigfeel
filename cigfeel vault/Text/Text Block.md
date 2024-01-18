#class

A text block defines a Transformable text area intended to stack on top of each other, like in a [[Text History]]. 

* Adheres to a predetermined width
* Calculates a dynamic height given the input string

```cpp
TextBlock(int width);
void setString(string s);
FloatRect getRect();
```

Eventually, this text block container can be extended to include any other type of predetermined styling, modifying the internal padding, adding drawables around the text, etc. 