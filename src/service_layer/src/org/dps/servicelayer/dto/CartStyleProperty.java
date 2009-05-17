package org.dps.servicelayer.dto;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name="cartstyleprop")
@XmlAccessorType(XmlAccessType.NONE)
public class CartStyleProperty extends Audit  {

	@Column(name="cart_style_prop_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartStylePropID;
	
	@Column(name="key", updatable=false)
	private String key;
	
	@Column(name="value")
	private String value;
	
	@ManyToOne()
	@JoinColumn(name="cart_style_id", nullable=false, insertable=false, updatable=false)
	private CartStyle style;
	
	@XmlElement(required = true)
	public Long getCartStylePropID() {
		return cartStylePropID;
	}
	protected void getCartStylePropID(Long id) {
		cartStylePropID = id;
	}

	@XmlElement(required = true)
	public String getKey() {
		return key;
	}
	protected void setKey(String key_) {
		key = key_;
	}

	@XmlElement(required = true)
	public String getValue() {
		return value;
	}
	public void setValue(String value_) {
		value = value_;
	}

	@XmlTransient
	public CartStyle getStyle() {
		return style;
	}
	protected void setStyle(CartStyle style_) {
		style = style_;
	}

	public String toString() {
		return key + ":" + value;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((cartStylePropID == null) ? 0 : cartStylePropID.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		CartStyleProperty other = (CartStyleProperty) obj;
		if (cartStylePropID == null) {
			if (other.cartStylePropID != null)
				return false;
		} else if (!cartStylePropID.equals(other.cartStylePropID))
			return false;
		return true;
	}
}
