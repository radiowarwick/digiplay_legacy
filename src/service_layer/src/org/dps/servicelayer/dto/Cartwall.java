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
import javax.persistence.ManyToOne;
import javax.persistence.MapKey;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name="cartwall")
@XmlAccessorType(XmlAccessType.PROPERTY)
public class Cartwall extends Audit  {

	@Column(name="cartwall_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartwallID;
	
	@Column(name="name")
	private String name;
	
	@Column(name="page", insertable=false, updatable=false)
	private Integer page;
		
	@Column(name="description")
	private String description;

	@ManyToOne(optional=false)
	@JoinColumn(name="cartset_id", nullable=false, insertable=false, updatable=false)
	private Cartset cartset;

	@OneToMany(cascade={CascadeType.ALL}, fetch = FetchType.EAGER)
	@JoinColumn(name="cartwall_id", nullable=false)
    @MapKey(name="cartID")
	private Map<Integer, CartAudio> carts = new HashMap<Integer, CartAudio>();
	
	@XmlElement(required = true)
	public Long getCartwallID() {
		return cartwallID;
	}
	protected void setCartwallID(Long id) {
		cartwallID = id;
	}

	@XmlElement(required = true)
	public String getName() {
		return name;
	}
	public void setName(String name_) {
		name = name_;
	}

	@XmlElement(required = true)
	public Integer getPage() {
		return page;
	}
	protected void setPage(Integer page_) {
		page = page_;
	}

	@XmlElement(required = true)
	public String getDescription() {
		return description;
	}
	public void setDescription(String description_) {
		description = description_;
	}

	@XmlTransient
	public Cartset getCartset() {
		return cartset;
	}
	protected void setCartset(Cartset cartset_) {
		cartset = cartset_;
	}

	public Map<Integer, CartAudio> getCarts() {
		return Collections.unmodifiableMap(carts);
	}
	public void addCart(Integer cartID, CartAudio cart) {
		cart.setCartwall(this);
		cart.setCartID(cartID);
		carts.put(cartID, cart);
	}
	public CartAudio deleteCart(Integer cartID) {
		CartAudio cart = carts.get(cartID);
		cart.setCartwall(null);
		carts.remove(cartID);
		return cart;
	}
	public CartAudio getCart(Integer cartID) {
		CartAudio cart = carts.get(cartID);
		return cart;
	}
	@XmlElement(required = true, name = "cart")
    @XmlElementWrapper(required = true, name = "carts")
	public Collection<CartAudio> getCartAudioCollection() {
		return carts.values();
	}
	public void setCartAudioCollection(Collection<CartAudio> cartsCol) {
		carts.clear();
		for(CartAudio ca : cartsCol) {
			carts.put(ca.getCartID(), ca);
		}
	}
	
	public String toString() {
		return name;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((cartwallID == null) ? 0 : cartwallID.hashCode());
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
		Cartwall other = (Cartwall) obj;
		if (cartwallID == null) {
			if (other.cartwallID != null)
				return false;
		} else if (!cartwallID.equals(other.cartwallID))
			return false;
		return true;
	}
}
