package org.dps.servicelayer.dto;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.MapKey;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name="cartstyle")
public class CartStyle extends Audit  {

	@Column(name="cart_style_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartStyleID;
	
	@Column(name="name")
	private String name;

	@Column(name="description")
	private String description;
	
	@OneToMany(cascade={CascadeType.ALL})
	@JoinColumn(name="cart_style_id", nullable=false)
    @MapKey(name="key")
	private Map<String, CartStyleProperty> properties = new HashMap<String, CartStyleProperty>();
	

	public Long getCartStyleID() {
		return cartStyleID;
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

	protected void setCartStyleID(Long cartStyleID_) {
		cartStyleID = cartStyleID_;
	}

	public String getName() {
		return name;
	}

	public void setName(String name_) {
		name = name_;
	}

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
