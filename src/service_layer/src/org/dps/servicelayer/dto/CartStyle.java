package org.dps.servicelayer.dto;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.MapKey;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

@Entity
@Table(name="cartstyle")
@XmlAccessorType(XmlAccessType.PROPERTY)
public class CartStyle extends Audit  {

	@Column(name="cart_style_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartStyleID;
	
	@Column(name="name")
	private String name;

	@Column(name="description")
	private String description;
	
	@OneToMany(cascade={CascadeType.ALL}, fetch = FetchType.EAGER)
	@JoinColumn(name="cart_style_id", nullable=false)
    @MapKey(name="key")
	private Map<String, CartStyleProperty> properties = new HashMap<String, CartStyleProperty>();
	
	@XmlElement(required = true)
	public Long getCartStyleID() {
		return cartStyleID;
	}
	protected void setCartStyleID(Long id) {
		cartStyleID = id;
	}

	public Map<String, CartStyleProperty> getProperties() {
		return Collections.unmodifiableMap(properties);
	}
	protected void setProperties(Map<String, CartStyleProperty> properties_) {
		properties = properties_;
	}
	public void addProperty(String key, String val) {
		CartStyleProperty prop = new CartStyleProperty();
		prop.setKey(key);
		prop.setValue(val);
		prop.setStyle(this);
		properties.put(key, prop);
	}
	public CartStyleProperty deleteProperty(String key) {
		CartStyleProperty prop = properties.get(key);
		properties.remove(key);
		return prop;
	}
	public CartStyleProperty getProperty(String key) {
		return properties.get(key);
	}
    @XmlElement(name = "cartStyleProperty", required = true)
    @XmlElementWrapper(name="cartStyleProperties", required = true)
	protected Collection<CartStyleProperty> getPropertiesCollection() {
		return properties.values();
	}
	protected void setPropertiesCollection(Collection<CartStyleProperty> propertyCol) {
		properties.clear();
		for(CartStyleProperty csp : propertyCol) {
			properties.put(csp.getKey(), csp);
		}
	}

	@XmlElement(required = true)
	public String getName() {
		return name;
	}
	public void setName(String name_) {
		name = name_;
	}

	@XmlElement(required = true)
	public String getDescription() {
		return description;
	}
	public void setDescription(String description_) {
		description = description_;
	}
	
	public String toString() {
		return name;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((cartStyleID == null) ? 0 : cartStyleID.hashCode());
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
		CartStyle other = (CartStyle) obj;
		if (cartStyleID == null) {
			if (other.cartStyleID != null)
				return false;
		} else if (!cartStyleID.equals(other.cartStyleID))
			return false;
		return true;
	}
}
