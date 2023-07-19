package com.tcompany.tracker.database

import kotlinx.serialization.ExperimentalSerializationApi
import kotlinx.serialization.KSerializer
import kotlinx.serialization.Serializable
import kotlinx.serialization.descriptors.SerialDescriptor
import kotlinx.serialization.encoding.Decoder
import kotlinx.serialization.encoding.Encoder

@Serializable(with = LazyDB.Serializer::class)
interface LazyDB<out T> {
    val id: Int?

    suspend fun value(): T

    fun isInitialized(): Boolean
    fun unsafeValue(): T

    companion object {
        fun <T> lazy(id: Int? = null, initializer: suspend (Int) -> T): LazyDB<T> = object : LazyDB<T> {
            private var value: T? = null

            override val id: Int? = id
            override suspend fun value(): T = value ?:
                initializer(id ?: throw IllegalAccessException("Trying to fetch a lazy without id and value"))
                    .apply { value = this }

            override fun isInitialized(): Boolean = value != null
            override fun unsafeValue(): T = value ?: throw IllegalAccessException("Trying to fetch a lazy without initialized value")
        }
    }

    class Serializer<T>(private val innerSerializer: KSerializer<T>) : KSerializer<LazyDB<T>> {
        @OptIn(ExperimentalSerializationApi::class)
        override val descriptor: SerialDescriptor = SerialDescriptor("LazyDB", innerSerializer.descriptor)

        override fun serialize(encoder: Encoder, value: LazyDB<T>) {
            if (value.isInitialized())
                innerSerializer.serialize(encoder, value.unsafeValue())
            else
                encoder.encodeInt(value.id ?: throw IllegalAccessException("Trying to serialize a db lazy without id"))
        }

        override fun deserialize(decoder: Decoder): LazyDB<T> {
            TODO()//return innerSerializer.deserialize(decoder).lazy()
        }
    }
}

fun <T> T.lazy(id: Int? = null): LazyDB<T> = object : LazyDB<T> {
    override val id: Int? = id
    override suspend fun value(): T = this@lazy
    override fun isInitialized(): Boolean = true
    override fun unsafeValue(): T = this@lazy
}