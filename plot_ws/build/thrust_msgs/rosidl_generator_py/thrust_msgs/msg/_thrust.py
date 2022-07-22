# generated from rosidl_generator_py/resource/_idl.py.em
# with input from thrust_msgs:msg/Thrust.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Thrust(type):
    """Metaclass of message 'Thrust'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('thrust_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'thrust_msgs.msg.Thrust')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__thrust
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__thrust
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__thrust
            cls._TYPE_SUPPORT = module.type_support_msg__msg__thrust
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__thrust

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Thrust(metaclass=Metaclass_Thrust):
    """Message class 'Thrust'."""

    __slots__ = [
        '_header',
        '_thrust',
        '_alpha',
        '_kp',
        '_ki',
        '_kd',
        '_kff',
        '_mode',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'thrust': 'double',
        'alpha': 'double',
        'kp': 'double',
        'ki': 'double',
        'kd': 'double',
        'kff': 'double',
        'mode': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.thrust = kwargs.get('thrust', float())
        self.alpha = kwargs.get('alpha', float())
        self.kp = kwargs.get('kp', float())
        self.ki = kwargs.get('ki', float())
        self.kd = kwargs.get('kd', float())
        self.kff = kwargs.get('kff', float())
        self.mode = kwargs.get('mode', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.thrust != other.thrust:
            return False
        if self.alpha != other.alpha:
            return False
        if self.kp != other.kp:
            return False
        if self.ki != other.ki:
            return False
        if self.kd != other.kd:
            return False
        if self.kff != other.kff:
            return False
        if self.mode != other.mode:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @property
    def thrust(self):
        """Message field 'thrust'."""
        return self._thrust

    @thrust.setter
    def thrust(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'thrust' field must be of type 'float'"
        self._thrust = value

    @property
    def alpha(self):
        """Message field 'alpha'."""
        return self._alpha

    @alpha.setter
    def alpha(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'alpha' field must be of type 'float'"
        self._alpha = value

    @property
    def kp(self):
        """Message field 'kp'."""
        return self._kp

    @kp.setter
    def kp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'kp' field must be of type 'float'"
        self._kp = value

    @property
    def ki(self):
        """Message field 'ki'."""
        return self._ki

    @ki.setter
    def ki(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ki' field must be of type 'float'"
        self._ki = value

    @property
    def kd(self):
        """Message field 'kd'."""
        return self._kd

    @kd.setter
    def kd(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'kd' field must be of type 'float'"
        self._kd = value

    @property
    def kff(self):
        """Message field 'kff'."""
        return self._kff

    @kff.setter
    def kff(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'kff' field must be of type 'float'"
        self._kff = value

    @property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value
