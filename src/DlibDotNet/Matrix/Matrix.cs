﻿using System;
using System.Collections.Generic;
using System.Linq;
using DlibDotNet.Extensions;

// ReSharper disable once CheckNamespace
namespace DlibDotNet
{

    public sealed class Matrix<T> : MatrixBase
        where T : struct
    {

        #region Fields

        private readonly MatrixElementTypes _MatrixElementTypes;

        private readonly Dlib.Native.MatrixElementType _ElementType;

        private static readonly Dictionary<Type, MatrixElementTypes> SupportTypes = new Dictionary<Type, MatrixElementTypes>();

        #endregion

        #region Constructors

        static Matrix()
        {
            var types = new[]
            {
                new { Type = typeof(byte),          ElementType = MatrixElementTypes.UInt8         },
                new { Type = typeof(ushort),        ElementType = MatrixElementTypes.UInt16        },
                new { Type = typeof(uint),          ElementType = MatrixElementTypes.UInt32        },
                new { Type = typeof(sbyte),         ElementType = MatrixElementTypes.Int8          },
                new { Type = typeof(short),         ElementType = MatrixElementTypes.Int16         },
                new { Type = typeof(int),           ElementType = MatrixElementTypes.Int32         },
                new { Type = typeof(float),         ElementType = MatrixElementTypes.Float         },
                new { Type = typeof(double),        ElementType = MatrixElementTypes.Double        },
                new { Type = typeof(RgbPixel),      ElementType = MatrixElementTypes.RgbPixel      },
                new { Type = typeof(RgbAlphaPixel), ElementType = MatrixElementTypes.RgbAlphaPixel },
                new { Type = typeof(HsiPixel),      ElementType = MatrixElementTypes.HsiPixel      }
            };

            foreach (var type in types)
                SupportTypes.Add(type.Type, type.ElementType);
        }

        public Matrix()
        {
            if (!SupportTypes.TryGetValue(typeof(T), out var type))
                throw new NotSupportedException($"{typeof(T).Name} does not support");

            this._MatrixElementTypes = type;
            this._ElementType = type.ToNativeMatrixElementType();
            this.NativePtr = Dlib.Native.matrix_new(this._ElementType);
        }

        public Matrix(int row, int column)
        {
            if (!SupportTypes.TryGetValue(typeof(T), out var type))
                throw new NotSupportedException($"{typeof(T).Name} does not support");
            if (row < 0)
                throw new ArgumentOutOfRangeException($"{nameof(row)}", $"{nameof(row)} should be positive value.");
            if (column < 0)
                throw new ArgumentOutOfRangeException($"{nameof(column)}", $"{nameof(column)} should be positive value.");

            this._MatrixElementTypes = type;
            this._ElementType = type.ToNativeMatrixElementType();
            this.NativePtr = Dlib.Native.matrix_new1(this._ElementType, row, column);
        }

        internal Matrix(IntPtr ptr, MatrixElementTypes type)
        {
            if (ptr == IntPtr.Zero)
                throw new ArgumentException("Can not pass IntPtr.Zero", nameof(ptr));

            this.NativePtr = ptr;
            this._MatrixElementTypes = type;
            this._ElementType = type.ToNativeMatrixElementType();
        }

        #endregion

        #region Properties

        public override int Columns
        {
            get
            {
                this.ThrowIfDisposed();
                Dlib.Native.matrix_nc(this._ElementType, this.NativePtr, out var ret);
                return ret;
            }
        }

        public override MatrixElementTypes MatrixElementType => this._MatrixElementTypes;

        public override int Rows
        {
            get
            {
                this.ThrowIfDisposed();
                Dlib.Native.matrix_nr(this._ElementType, this.NativePtr, out var ret);
                return ret;
            }
        }

        public int Size
        {
            get
            {
                this.ThrowIfDisposed();
                Dlib.Native.matrix_size(this._ElementType, this.NativePtr, out var ret);
                return ret;
            }
        }

        #endregion

        #region Methods

        public void Assign(T[] array)
        {
            switch (this._MatrixElementTypes)
            {
                case MatrixElementTypes.UInt8:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<byte>().ToArray());
                    break;
                case MatrixElementTypes.UInt16:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<ushort>().ToArray());
                    break;
                case MatrixElementTypes.UInt32:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<uint>().ToArray());
                    break;
                case MatrixElementTypes.Int8:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<sbyte>().ToArray());
                    break;
                case MatrixElementTypes.Int16:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<short>().ToArray());
                    break;
                case MatrixElementTypes.Int32:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<int>().ToArray());
                    break;
                case MatrixElementTypes.Float:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<float>().ToArray());
                    break;
                case MatrixElementTypes.Double:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<double>().ToArray());
                    break;
                case MatrixElementTypes.RgbPixel:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<RgbPixel>().ToArray());
                    break;
                case MatrixElementTypes.RgbAlphaPixel:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<RgbAlphaPixel>().ToArray());
                    break;
                case MatrixElementTypes.HsiPixel:
                    Dlib.Native.matrix_operator_array(this._ElementType, this.NativePtr, array.Cast<HsiPixel>().ToArray());
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        #region Overrides

        protected override void DisposeUnmanaged()
        {
            base.DisposeUnmanaged();
            Dlib.Native.matrix_delete(this._ElementType, this.NativePtr);
        }

        public override string ToString()
        {
            var ofstream = IntPtr.Zero;
            var stdstr = IntPtr.Zero;
            string str = null;

            try
            {
                ofstream = Dlib.Native.ostringstream_new();
                var ret = Dlib.Native.matrix_operator_left_shift(this._ElementType, this.NativePtr, ofstream);
                switch (ret)
                {
                    case Dlib.Native.ErrorType.OK:
                        stdstr = Dlib.Native.ostringstream_str(ofstream);
                        str = StringHelper.FromStdString(stdstr);
                        break;
                    case Dlib.Native.ErrorType.InputElementTypeNotSupport:
                        throw new ArgumentException($"Input {this._ElementType} is not supported.");
                    default:
                        throw new ArgumentException();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
            finally
            {
                if (stdstr != IntPtr.Zero)
                    Dlib.Native.string_delete(stdstr);
                if (ofstream != IntPtr.Zero)
                    Dlib.Native.ostringstream_delete(ofstream);
            }
            
            return str;
        }

        #endregion

        #endregion

    }

}