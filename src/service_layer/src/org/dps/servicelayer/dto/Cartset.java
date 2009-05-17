package org.dps.servicelayer.dto;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import org.hibernate.annotations.IndexColumn;

@Entity
@Table(name="cartset")
@PrimaryKeyJoinColumn(name="file_id")
@XmlAccessorType(XmlAccessType.NONE)
public class Cartset extends File  {
	
	@Column(name="name")
	private String name;
	
	@Column(name="description")
	private String description;
	
	@OneToMany(cascade={CascadeType.ALL}, fetch=FetchType.LAZY)
	@JoinColumn(name="cartset_id", nullable=false, updatable=true, insertable=true)
	@IndexColumn(name="page", nullable=false, base=0)
	private List<Cartwall> cartwalls = new ArrayList<Cartwall>();

	public Cartset() {
		super(Constants.FILE_TYPE_CARTSET);
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

	@XmlElement(required = true, name = "cartwall")
	@XmlElementWrapper(name="cartwalls", required = true)
	public List<Cartwall> getCartwalls() {
		return Collections.unmodifiableList(cartwalls);
	}
	public Cartwall getCartwall(Integer page) {
		return cartwalls.get(page.intValue());
	}
	public void addCartwall(Cartwall cartwall) {
		cartwall.setCartset(this);
		cartwalls.add(cartwall);
	}
	public Cartwall removeCartwall(Cartwall cartwall) {
		Cartwall out = null;
		for(Cartwall wall : cartwalls) {
			if(wall.equals(cartwall)) {
				out = wall;
				continue;
			}
		}
		if(out != null) {
			out.setCartset(null);
			cartwalls.remove(out);
		}
		return out;
	}
	public Cartwall removeCartwall(Integer page) {
		Cartwall out = cartwalls.get(page.intValue());
		if(out != null) {
			out.setCartset(null);
			cartwalls.remove(out);
		}
		return out;
	}

	public String toString() {
		return name;
	}
	
	public void makeSafe() {
		//TODO make sure this can't be compiled out...
		getCartwalls().size();
	}
}
